#include "CPipe.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <pthread.h>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

using namespace std;

const string NEWLINE_CMD = " ";

CPipe::CPipe(bool debugMode)
{
	setbuf(stdin, NULL); // remove buffer to ensure commands are recieved immediataley.
	setbuf(stdout, NULL); // remove buffer to ensure commands are sent immediataley.
	inputMessageQueue.clear();
	outputMessageQueue.clear();
	this->isRunning = true;
	this->debugMode = debugMode;
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

string CPipe::dequeueInputMessage() {
	// nothing to do if there are no messages
	if(0 == inputMessageQueue.size()) {
		return "";
	}

	// get the message
	string message = inputMessageQueue[inputMessageQueue.size() - 1];
	// remove the retrieved message from the queue
	inputMessageQueue.pop_back();

	return message;
}

void CPipe::queueInputMessage(string message) {
	cout << "stage three passed " << endl;
	this->inputMessageQueue.insert(inputMessageQueue.begin(), message);
}

string CPipe::dequeueOutputMessage() {
	// nothing to do if there are no messages
	if (0 == outputMessageQueue.size()) {
		return "";
	}

	// get the message
	string message = outputMessageQueue[outputMessageQueue.size() - 1];
	// remove the retrieved message from the queue
	outputMessageQueue.pop_back();

	return message;
}

void CPipe::queueOutputMessage(string message) {
	this->outputMessageQueue.insert(outputMessageQueue.begin(), message);
}

void CPipe::xboard() {
	//d("xboard");
	queueOutputMessage(NEWLINE_CMD);
}

void CPipe::protover(string version) {
	//d("protocol version " + version);
	queueOutputMessage("feature done=0");
	queueOutputMessage("feature ping=1");
	queueOutputMessage("feature usermove=1");
	queueOutputMessage("feature done=1");
}

void CPipe::featureResponse(bool accepted, string featureName) {
	d("feature '" + featureName + "': " + (accepted ? "accepted" : "rejected"));
}

void CPipe::newGame() {
	d("new game.");
}

void CPipe::variant(string variant) {
	d("variant: " + variant);
}
void CPipe::random() {
	d("random mode toggle");
}

void CPipe::force() {
	d("enter force mode");
}

void CPipe::go() {
	d("go - begin playing for color on move");
}

void CPipe::white() {
	d("opponent: white | engine: black");
}

void CPipe::black() {
	d("opponent: black | engine: white");
}

void CPipe::userMove(string move) {
	// TODO: validate and translate move before sending to engine.

	// for fun adding this to see how UI responds
	queueOutputMessage("move e7e5");
}

void CPipe::moveNow() {
	// TODO: engine should return current best move, if any.
}

void CPipe::ping(string val) {
	queueOutputMessage("pong " + val);
}

void CPipe::opponentName(string name) {
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
	string cmd;
	do {
		if("" != (cmd = dequeueOutputMessage())) {
			cout << (debugMode ? "[OUTPUT] " : "" ) << cmd << endl;
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
	string cmd;

	do {
		// TODO: look into behavious of this line. It accepts ALL input, even non-textual.
		//		 (e.g. <up_arrow><down_arrow>quit evaluate to "quit", except it does not match the rule below)
		cin >> skipws >> cmd;

		if("xboard" == cmd) {
			xboard();
		}
		else if("protover" == cmd) {
			string arg;
			cin >> skipws >> arg;
			protover(arg);
		}
		else if("accepted" == cmd) {
			string arg;
			cin >> skipws >> arg;
			featureResponse(true, arg);
		}
		else if("rejected" == cmd) {
			string arg;
			cin >> skipws >> arg;
			featureResponse(false, arg);
		}
		else if("new" == cmd) {
			newGame();
		}
		else if("variant" == cmd) {
			string arg;
			cin >> skipws >> arg;
			variant(arg);
		}
		else if("random" == cmd) {
			random();
		}
		else if("force" == cmd) {
			force();
		}
		else if("go" == cmd) {
			go();
		}
		else if("white" == cmd) {
			white();
		}
		else if ("black" == cmd) {
			black();
		}
		else if("usermove" == cmd) {
			string arg;
			cin >> skipws >> arg;
			userMove(arg);
		}
		else if("?" == cmd) {
			moveNow();
		}
		else if("ping" == cmd.substr(0, 4)) {
			string args;
			cin >> skipws >> args;
			ping(args);
		}
		else if("name" == cmd) {
			string arg;
			cin >> skipws >> arg;
			opponentName(arg.substr(5, 2));
		}
		else if("pause" == cmd) {
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

void CPipe::d(const char* message) {
	// TODO: use globally defined param to determine whether to print.
	if(this->debugMode) {
		cout << "[DEBUG] " << message << endl;
	}
}

void CPipe::d(const string message) {
	d(message.c_str());
}
