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
  firstTime = true;
}


void CBaumhausengine::analyzePos() {
	// TODO Main thinking logic would probably be here..
  std::string tempMove;
  std::cout << firstTime << std::endl;
  movesList.clear();
		std::vector<std::string> possibleMoves = position->getPossibleMoves(false); // TODO change the hardcoded 'false' to the actual current color
    std::cout << "got the movesList" << std::endl;
    std::cout << possibleMoves.size() << std::endl;
    if (possibleMoves.size() > 0) {
			movesList = possibleMoves;
      std::cout << "setting seed" << std::endl;
      srand (time(NULL));
      std::cout << "random will be generated" << std::endl;
      tempMove = possibleMoves [rand() % possibleMoves.size()];
      std::cout << tempMove << std::endl;
    	makeMove(tempMove);
    }
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
  //remove the old piece pointer and set it otherwhere.
  std::vector<int> moveStartField = CPos::coordFromName (move.substr (0, 2));
  std::vector<int> moveEndField = CPos::coordFromName (move.substr (2, 2));

  CSquare* startSquare = position->getSquarePointer (moveStartField [0], moveStartField[1]);
  CSquare* endSquare = position -> getSquarePointer (moveEndField[0], moveEndField[1]);

  if (startSquare->getPiecePointer()->getColor() == false /*this-> colorOnTurn*/) {
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          if (endSquare->getPiecePointer()->getColor() != this-> colorOnTurn) { //checks if the piece is of the same color

          } else {
              endSquare->takePiece();
              endSquare->setPiecePointer(startSquare->removePiece());
              endSquare->getPiecePointer () -> setCoordinates (moveEndField [0], moveEndField[1]);
          }
      } else {
          endSquare->setPiecePointer (startSquare->removePiece());
          endSquare->getPiecePointer () -> setCoordinates (moveEndField [0], moveEndField[1]);
      }
    // update position to reflect move
    pipe->queueOutputMessage("move " + move); //output the current move
    this->colorOnTurn = !this->colorOnTurn; //change the player color
    pipe->d("color on turn: " + std::to_string(colorOnTurn)); //output whose turn it is
  } else {

  }
}
