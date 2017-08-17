#include "baumhausengine.h"

#include <string>
#include <iostream>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CBaumhausengine::CBaumhausengine(bool debugMode)
{
    this->position = new CPos();
    this->pipe = new CPipe(debugMode);
	  this->debugMode = debugMode;
    this->init(); //might be not used... If so remove it. Initially used for debug
    //ctor
}

CBaumhausengine::~CBaumhausengine()
{
	delete this->position;
	delete this->pipe;
    //dtor
}

void CBaumhausengine::init() {
	this->random = false; // by default random is off
	this->colorOnTurn = true; // white starts the match
	this->color = false; // engine will play black
  position->feedFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"); //not the true starting position, but a starting position that is used 4 debug
	pipe->d("End - init()");
}

bool firstTime = false;

void CBaumhausengine::analyzePos() {
	// TODO Main thinking logic would probably be here.
  std::cout<< "barrier 0 passed!" << std::endl;
  position->getPossibleMoves(false);
  std::cout<< "barrier one passed!" << std::endl;
	// . . .
  std::string tempMove;
	// we should have candidate move now.
  movesList.clear();
  movesList.insert(movesList.end(), position->getPossibleMoves(false).begin(), position->getPossibleMoves(false).end());
  if (firstTime == true) {
  	tempMove = "e7e5";
    firstTime = false;
  } else {
    tempMove == movesList [0];
  }
	makeMove(tempMove);
	pipe->queueOutputMessage("move " + tempMove);
}

void CBaumhausengine::ponderPos() {

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

	std::cout << "Baumhaus Engine started up... Waiting for Signals";

	std::string message;
	while (true) { //just simply spools to wait for a signal
    		std::string message = pipe->dequeueInputMessage(false);
        if (message != "") {std::cout << message << " <<<< The gotten Message" << std::endl;}

    		if("quit" == message) {
    			break;
    		}
    		else if ("new" == message) {
    			init();
    		}
    		else if("ping" == message.substr(0, 4)) {
    			pong(pipe->dequeueInputMessage(true));
    		}
    		else if("random" == message) {
    			this->random = !this->random;
    		}
    		else if ("usermove" == message) { //quick and dirty way. needs to be made better
          std::cout << "Got usermove request" << std::endl;
          analyzePos();
    			//std::string move = pipe->dequeueInputMessage(true);
    			// validate move
    			// TODO

          // we've handled the message (assimung there was one), we can continue pondering/thinking
          /*if(this->color == this->colorOnTurn) { // engine's turn
                this->analyzePos();
          } else {
                this->ponderPos();
          }*/
    			// if validation checks out. make the move.
    			//makeMove(move);
  		  }
	}

	pipe->d("Goodbye!");
}

void CBaumhausengine::pong(std::string val) {
	this->pipe->queueOutputMessage("pong " + val);
  std::cout << "Got Pong request" << std::endl;
}

void CBaumhausengine::makeMove(std::string move) {
	// update position to reflect move

	// other color's turn
	this->colorOnTurn = !this->colorOnTurn;
	pipe->d("color on turn: " + std::to_string(colorOnTurn));
}
