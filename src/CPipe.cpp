#include "CPipe.h"

#include <string>
#include <iostream>
#include <cstdio>
/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

using namespace std;
void d(const char* str);
void d(const string str);

CPipe::CPipe(bool debugMode)
{
	setbuf(stdin, NULL); // remove buffer to ensure commands are recieved immediataley.
    messageStack.clear();
	this->debugMode = debugMode;
    //ctor
}

CPipe::~CPipe()
{
    //dtor
}

std::string CPipe::getLastMessage() {
    return messageStack[messageStack.size()]; //returns the last message logged
}

void CPipe::xboard() {
	d("xboard");
}

void CPipe::protover(string version) {
	d("protocol version " + version); 
}

void CPipe::featureResponse(bool accepted) {
	d("feature response: " + accepted);
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
}

void CPipe::moveNow() {
	// TODO: engine should return current best move, if any.
}

void CPipe::ping() {
	// TODO: respond with a 'pong', but only after completeing all pending commands.
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

void CPipe::run() { // consnider allowing other input streams

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
			featureResponse(true);
		}
		else if("rejected" == cmd) {
			featureResponse(false);
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
		else if("ping" == cmd) {
			ping();
		}
		else if("name" == cmd) {
			string arg;
			cin >> skipws >> arg;
			opponentName(arg);
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
		d("command: " + cmd);

	} while(cmd != "quit");

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