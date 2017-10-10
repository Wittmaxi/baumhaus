#include "CPipe.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <pthread.h>
#include <mutex>
#include <sstream>


/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPipe* pipe = CPipe::getInstance();


const std::string NEWLINE_CMD = " ";
const std::string DEBUG_TAG = "[DEBUG] ";

// Must explicitly refrence self here

CPipe* CPipe::self = nullptr;




CPipe* CPipe::getInstance() {
	if(!self) {
		self = new CPipe();
	}
	return self;
}

void CPipe::init(bool debugMode) {
	this->debugMode = debugMode;
}

CPipe::CPipe()
{
	setbuf(stdin, NULL); // remove buffer to ensure commands are recieved immediataley.
	setbuf(stdout, NULL); // remove buffer to ensure commands are sent immediataley.
	inputMessageQueue.clear();
	outputMessageQueue.clear();
	this->isRunning = true;
	// begin the IO threads
	pthread_create(&(this->inThread), NULL, CPipe::startInputThread, this);
	pthread_create(&(this->outThread), NULL, CPipe::startOutputThread, this);
    //ctor
}

CPipe::~CPipe()
{
	this->isRunning = false;
	// wait for both threads to finish operations.
	pthread_join(this->inThread, NULL);
	pthread_join(this->outThread, NULL);
    //dtor
}

std::string CPipe::dequeueInputMessage(bool waitForMessage) {
	// nothing to do if there are no messages
	if(!waitForMessage && 0 == inputMessageQueue.size()) {
		return "";
	}

	while(0 == inputMessageQueue.size()); // block until message has appeared.

	inputMutex.lock();
	// get the message
	std::string message = inputMessageQueue[inputMessageQueue.size() - 1];
	// remove the retrieved message from the queue
	inputMessageQueue.pop_back();
	inputMutex.unlock();

	return message;
}

void CPipe::queueInputMessage(std::string message) {
	inputMutex.lock();
	this->inputMessageQueue.insert(inputMessageQueue.begin(), message);
	inputMutex.unlock();
}

std::string CPipe::dequeueOutputMessage(bool waitForMessage) {
	// nothing to do if there are no messages
	if (!waitForMessage && 0 == outputMessageQueue.size()) {
		return "";
	}

	while(0 == outputMessageQueue.size());

	outputMutex.lock();
	// get the message
	std::string message = outputMessageQueue[outputMessageQueue.size() - 1];
	// remove the retrieved message from the queue
	outputMessageQueue.pop_back();
	outputMutex.unlock();

	return message;
}

void CPipe::queueOutputMessage(std::string message) {
	outputMutex.lock();
	this->outputMessageQueue.insert(outputMessageQueue.begin(), message);
	outputMutex.unlock();
}

void CPipe::xboard() {
	//d("xboard");
	queueOutputMessage(NEWLINE_CMD);
}

void CPipe::protover(std::string version) {
	//d("protocol version " + version);
	queueOutputMessage("feature done=0"); // let XBorad know we are not done with the feature commands
	queueOutputMessage("feature ping=1");
	queueOutputMessage("feature usermove=1");
	queueOutputMessage("feature done=1"); // let XBoard know we are done with the feature commands
}

void CPipe::featureResponse(bool accepted, std::string featureName) {
	d("feature '" + featureName + "': " + (accepted ? "accepted" : "rejected"));
	// TODO: perhaps store the responses in case we have to alter behavior
}

void CPipe::newGame() {
	d("new game.");
	queueInputMessage("new");
}

void CPipe::variant(std::string variant) {
	d("variant: " + variant);
}
void CPipe::random() {
	d("random mode toggle");
	queueInputMessage("random");
}

void CPipe::force() {
	d("enter force mode");
}

void CPipe::go() {
	d("go - begin playing for color on move");
  queueInputMessage("go");
}

void CPipe::white() {
	d("opponent: white | engine: black");
  queueInputMessage("white");
}

void CPipe::black() {
	d("opponent: black | engine: white");
  queueInputMessage("black");
}

void CPipe::setLevel(std::string movesPerTimeControl, std::string base, std::string increment) {
	int delimiterPos = base.find(':');
	// split min and sec parts
	std::string minStr = delimiterPos == std::string::npos ? base : base.substr(0, delimiterPos);
	std::string secStr = delimiterPos == std::string::npos ? "0" : base.substr(delimiterPos + 1);
	// base time = min + seconds
	int totalSeconds = std::stoi(minStr) * 60 + std::stoi(secStr);
	// base time. convert to centiseconds immediately
	std::string centStr = std::to_string(totalSeconds*100);
	// increment time. convert to centiseconds immediately
	int incInt = std::stoi(increment);
	std::string incStr = std::to_string(incInt * 100);
	d("level setting - mps: " + movesPerTimeControl + " moves");
	d("level setting - base: " + minStr + "m " + secStr + "s - " + centStr);
	d("level setting - inc: " + incStr);

	// determine total times in centiseconds;

	queueInputMessage("level");
	queueInputMessage(movesPerTimeControl);
	queueInputMessage(centStr);
	queueInputMessage(incStr);
}

void CPipe::setTime(int centiseconds) {
	// TODO
}

void CPipe::setOpponentTime(int centiseconds) {
	// TODO
}

void CPipe::userMove(std::string move) {
	// TODO: validate and translate move before sending to engine.

	queueInputMessage("usermove");
	queueInputMessage(move);

	// for fun adding this to see how UI responds
	//queueOutputMessage("move e7e5");
}

void CPipe::moveNow() {
	// TODO: engine should return current best move, if any.
}

void CPipe::ping(std::string val) {
	queueInputMessage("ping");
	queueInputMessage(val);
}

void CPipe::togglePondering(bool ponder) {
	d("Pondering: " + std::to_string(ponder));
	queueInputMessage("ponder");
	queueInputMessage(std::to_string(ponder));
}

void CPipe::togglePonderingOutput(bool showOutput) {
	d("Show pondering output: " + std::to_string(showOutput));
	// TODO NOW
}

void CPipe::opponentName(std::string name) {
	d("Hi " + name + "!");
}

void CPipe::pause() {
	// TODO: have engine pause. i.e. stop all pondering and thinking, not force mode.
}

void CPipe::resume() {
	// TODO: resume pondering or thinking.
}

void* CPipe::startOutputThread(void* instance) {
	CPipe* pipe = (CPipe*)instance;
	pipe->d("Begin output monitoring");
	pipe->startOutput();
	pipe->d("End output monitoring");
	pthread_exit(NULL);
}

void CPipe::startOutput() {
	std::string cmd;
	do {
		if("" != (cmd = dequeueOutputMessage(false))) {
			std::cout << cmd << std::endl;
		}
	} while(isRunning);
}

void* CPipe::startInputThread(void* instance) {
	CPipe* pipe = (CPipe*)instance;
	pipe->d("Begin input monitoring");
	pipe->startInput();
	pipe->d("End input monitoring");
	pthread_exit(NULL);
}

void CPipe::startInput() {
	std::string cmd;

	do {
		// TODO: look into behavious of this line. It accepts ALL input, even non-textual.
		//		 (e.g. <up_arrow><down_arrow>quit evaluate to "quit", except it does not match the rule below)
		std::cin >> std::skipws >> cmd;
		if ("xboard" == cmd) {
			xboard();
		}
		else if ("protover" == cmd) {
			std::string arg;
			arg = readNext(true);
			protover(arg);
		}
		else if ("accepted" == cmd) {
			std::string arg;
			arg = readNext(true);
			featureResponse(true, arg);
		}
		else if ("rejected" == cmd) {
			std::string arg;
			arg = readNext(true);
			featureResponse(false, arg);
		}
		else if ("new" == cmd) {
			newGame();
		}
		else if ("variant" == cmd) {
			std::string arg;
			arg = readNext(true);
			variant(arg);
		}
		else if ("random" == cmd) {
			random();
		}
		else if ("force" == cmd) {
			force();
		}
		else if ("go" == cmd) {
			go();
		}
		else if ("white" == cmd) {
			white();
		}
		else if ("black" == cmd) {
			black();
		}
		else if ("level" == cmd) {
			std::string arg1, arg2, arg3;
			arg1 = readNext();
			arg2 = readNext();
			arg3 = readNext(true);
			setLevel(arg1, arg2, arg3);
		}
		else if ("usermove" == cmd) {
			std::string arg;
			arg = readNext(true);
			userMove(arg);
		}
		else if ("?" == cmd) {
			moveNow();
		}
		else if ("ping" == cmd) {
			std::string arg;
			arg = readNext(true);
			ping(arg);
		}
		else if ("hard" == cmd) {
			togglePondering(true);
		}
		else if ("easy" == cmd) {
			togglePondering(false);
		}
		else if ("post" == cmd) {
			togglePonderingOutput(true);
		}
		else if ("nopost" == cmd) {
			togglePonderingOutput(false);
		}
		else if ("name" == cmd) {
			std::string arg;
			arg = readNext(true);
			opponentName(arg);
		}
		else if ("pause" == cmd) {
			pause();
		}
		else if ("resume" == cmd) {
			resume();
		}
		else {
			// TODO: perhaps log the appropriate error if the command was supposed to be a move
		}
		//d("command: " + cmd);

	} while(isRunning && "quit" != cmd);

	isRunning = false;

	this->queueInputMessage("quit");
}

void CPipe::d(const char* message, bool newLine, bool writeDebug) {
	// TODO: use globally defined param to determine whether to print.
	if(this->debugMode) {
		if (writeDebug) {
			std::cout << DEBUG_TAG;
		}
		
    std::cout << message;
		
    if (newLine == true) {
			std::cout << std::endl; // this way, the user can choose, wether he wants to output a new line or not
		}
	}
}

void CPipe::d(const std::string message, bool newLine, bool writeDebug) {
	d(message.c_str(), newLine, writeDebug);
}

void CPipe::d(const int message, bool newLine, bool writeDebug) { //for anything else than strings
	d(std::to_string(message), newLine, writeDebug);
}

void CPipe::d(const float message, bool newLine, bool writeDebug) { //for anything else than strings
	d(std::to_string(message), newLine, writeDebug);
}

void CPipe::d(const double message, bool newLine, bool writeDebug ) { //for anything else than strings
	d(std::to_string(message), newLine, writeDebug);
}

void CPipe::d(const bool message, bool newLine, bool writeDebug) {
	d(std::to_string(message), newLine, writeDebug);
}



std::string CPipe::readNext(bool readToEnd) {
	std::string str;
	
	if(readToEnd) {
		std::getline(std::cin, str);
		str = ltrim(str);
	} else {
		std::cin >> std::skipws >> str;
	}

	return str;
}

// helper functions to convert to string
std::string str(int value) {
	return std::to_string(value);
}
std::string str(long value) {
	return std::to_string(value);
}
std::string str(long long value) {
	return std::to_string(value);
}
std::string str(unsigned value) {
	return std::to_string(value);
}
std::string str(unsigned long value) {
	return std::to_string(value);
}
std::string str(unsigned long long value) {
	return std::to_string(value);
}
std::string str(float value) {
	return std::to_string(value);
}
std::string str(double value) {
	return std::to_string(value);
}
std::string str(long double value) {
	return std::to_string(value);
}
std::string ltrim(std::string str) {
	return str.erase(0, str.find_first_not_of(' '));
}
