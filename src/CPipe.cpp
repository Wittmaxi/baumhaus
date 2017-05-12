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

CPipe::CPipe()
{
	setbuf(stdin, NULL); // remove buffer to ensure commands are recieved immediataley.
    messageStack.clear();
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

void CPipe::run() { // consnider allowing other input streams

	string cmd;

	do {
		// TODO: look into behavious of this line. It accepts ALL input, even non-textual. 
		//		 (e.g. <up_arrow><down_arrow>quit evaluate to "quit", except it does not match the rule below)
		cin >> skipws >> cmd;
		if(cmd == "xboard") xboard();
		else if(cmd == "protover") {
			string arg;
			cin >> skipws >> arg;
			protover(arg);
		}
		else if (cmd == "accepted") featureResponse(true);
		else if (cmd == "rejected") featureResponse(false);
		else {
			// perhaps log the appropriate error if the command was supposed to be a move
		}
		cout << "command: " << cmd << endl << endl;

	} while(cmd != "quit");

}

void d(const char* str) {
	// TODO: use globally defined param to determine whether to print.
	cout << "[DEBUG] " << str << endl;
}

void d(const string str) {
	d(str.c_str());
}