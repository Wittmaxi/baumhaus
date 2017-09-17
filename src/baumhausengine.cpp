#include "baumhausengine.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <time.h>


/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CBaumhausengine::CBaumhausengine()
{
    this->position = new CPos(); //creates a new position
    this->init(); //might be not used... If so remove it. Initially used for debug @awais you knwo the XBoard protocol better
    //ctor
}

CBaumhausengine::~CBaumhausengine()
{
	delete this->position; 
    //dtor
}

void CBaumhausengine::init() {
	this->random = false; // by default random is off
	this->colorOnTurn = true; // white starts the match
  this->color = false; //what color the engine has to play
  position->setColor(this->colorOnTurn); //set the color of the position to white
  position->emptyCells(); //remove every possible piece in CPos
  position->feedFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"); //feed the starting fen
}


void CBaumhausengine::analyzePos() {
	// TODO Main thinking logic would probably be here..
  movesList.clear();
	std::vector<std::string> possibleMoves = position->getPossibleMoves(colorOnTurn); // TODO change the hardcoded 'false' to the actual current color
  if (possibleMoves.size() > 0) { //if there are any legal moves
		movesList = possibleMoves; // copy the possible moves into an array
    /* WILL BE EXCHANGED BY ANALYSIS FUNCTIONS*/
    srand (time(NULL)); //randomize 
   	makeMove(possibleMoves [rand() % possibleMoves.size()]); //pick a random move
  } 
}

void CBaumhausengine::ponderPos() { //basically bruteforces in the background while the enemy is thinking

}

void CBaumhausengine::setColor(bool colorI) { //the playing-color
    color = colorI;
}

void CBaumhausengine::startRoutine() {
  pipe -> d ("THE BAUMHAUS-ENGINE WAS STARTED!");

	while (true) { //just simply spools to wait for a signal
    		std::string message = pipe->dequeueInputMessage(false);
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
          makeMove (pipe->dequeueInputMessage(true).substr(1, 4));
          analyzePos();
  		  }
	}

}

void CBaumhausengine::pong(std::string val) { //if the engine gets pinged, pong pack
	pipe->queueOutputMessage("pong " + val);
}

void CBaumhausengine::makeMove(std::string move) {
  //remove the old piece pointer and set it otherwhere.
    position -> movePointers (move);
    // update position to reflect move
    if (this->colorOnTurn == color) { //if its the engines turn, else, only move the piece pointers
      pipe->queueOutputMessage("move " + move);
    } //output the current move
    this->colorOnTurn = !this->colorOnTurn; //change the player color
    position -> setColor(colorOnTurn);
}
