#include "baumhausengine.h"

#include <string>
#include <iostream>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

using namespace std;

CBaumhausengine::CBaumhausengine(bool debugMode)
{
    this->position = new CPos;
    this->pipe = new CPipe(debugMode);
	this->debugMode = debugMode;
    //ctor
}

CBaumhausengine::~CBaumhausengine()
{
	delete this->position;
	delete this->pipe;
    //dtor
}

void CBaumhausengine::analyzePos(CPos position) {

}

void CBaumhausengine::updateSquares() {

}

void CBaumhausengine::setColor(bool colorI) { //the playing-color
    color = colorI;
}

bool CBaumhausengine::getColor() {
    return color;
}

void CBaumhausengine::startRoutine() {

	cout << "Baumhaus Engine started up... Waiting for Signals";


	while (true) { //just simply spools to wait for a signal
		string message = pipe->dequeueInputMessage(false);

		if("quit" == message) {
			break;
		} else if("ping" == message) {
			pong(pipe->dequeueInputMessage(true));
		}
	}

	pipe->d("Goodbye!");
}

void CBaumhausengine::pong(string val) {
	this->pipe->queueOutputMessage("pong " + val);
}
