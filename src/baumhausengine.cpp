#include "baumhausengine.h"

#include <string>
#include <pthread.h>
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
	pthread_create(&(this->pipeThread), NULL, CPipe::callRun, this->pipe);
    //ctor
}

CBaumhausengine::~CBaumhausengine()
{
	pthread_join(this->pipeThread, NULL); // wait for the pipeThread to terminate.
    //dtor
}

std::string CBaumhausengine::readPipe() {
    return pipe->getLastMessage();
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
	string message;
	while (true) { //just simply spools to wait for a signal
		message = pipe->getLastMessage();
		
		if("quit" == message) {
			break;
		}	
	}
	cout << "Goodbye!" << endl;
}
