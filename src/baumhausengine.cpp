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

std::string CBaumhausengine::readPipe() {
    return pipe->dequeueInputMessage();
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

	pipe->d("Baumhaus Engine started up... Waiting for Signals");

	string message;
	while (true) { //just simply spools to wait for a signal
		message = pipe->dequeueInputMessage();
		
		if("quit" == message) {
			break;
		}	
	}

	pipe->d("Goodbye!");
}
