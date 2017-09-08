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
  position->feedFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
	pipe->d("End - init()");
  firstTime = true;
}


void CBaumhausengine::analyzePos() {
	// TODO Main thinking logic would probably be here..
  std::string tempMove;
  std::cout << firstTime << std::endl;
  movesList.clear();
		std::vector<std::string> possibleMoves = position->getPossibleMoves(false); // TODO change the hardcoded 'false' to the actual current color
    std::cout << possibleMoves.size() << std::endl;
    if (possibleMoves.size() > 0) {
			movesList = possibleMoves;
      for (int i = 0; i < movesList.size(); i++) {std::cout << movesList[i] << std::endl;}
      srand (time(NULL));
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
          movePointers (pipe->dequeueInputMessage(true).substr(1, 4));
          analyzePos();
          this->colorOnTurn != this->colorOnTurn;
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
    movePointers (move);
    // update position to reflect move
    pipe->queueOutputMessage("move " + move); //output the current move
    this->colorOnTurn = !this->colorOnTurn; //change the player color
    pipe->d("color on turn: " + std::to_string(colorOnTurn)); //output whose turn it is
}

bool CBaumhausengine::movePointers (std::string move) {
  std::cout << "in movePointers_" << move << std::endl;
  std::cout << "no return type" << std::endl;
  std::vector<int> moveStartField = CPos::coordFromName (move.substr (0, 2));
  std::cout << "cord 1" << std::endl;
  std::vector<int> moveEndField = CPos::coordFromName (move.substr (2, 2));
  std::cout << "cord 2" << std::endl;

  std::cout << "declaring vars" << moveStartField[0] << moveStartField[1] << std::endl;
  CSquare* startSquare = position->getSquarePointer (moveStartField [0], moveStartField[1]);
  std::cout << "declared variable 1!" << moveStartField[0] << moveStartField[1] << std::endl;
  CSquare* endSquare = position -> getSquarePointer (moveEndField[0], moveEndField[1]);
  std::cout << "declared variables!" << std::endl;

  if (startSquare->containsPiece() == false)  {return false;} // if there is no piece in the start square, return an error

  std::cout << "to play: " << this -> colorOnTurn << startSquare->getPiecePointer()->getColor() << std::endl;
  if (startSquare->getPiecePointer()->getColor() == this-> colorOnTurn) {
      std::cout << "pointer is correct" << std::endl;
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          std::cout << "contains piece" << std::endl;
          if (endSquare->getPiecePointer()->getColor() == this-> colorOnTurn) { //checks if the piece is of the same color
              return false;
              std::cout << "error" << std::endl;
          } else {
              std::cout << "taking enemy piece" << std::endl;
              endSquare->takePiece();
              endSquare->setPiecePointer(startSquare->removePiece());
              endSquare->getPiecePointer () -> setCoordinates (moveEndField [0], moveEndField[1]);
          }
      } else {
          endSquare->setPiecePointer (startSquare->removePiece());
          endSquare->getPiecePointer () -> setCoordinates (moveEndField [0], moveEndField[1]);
      }
    } else {
      return false;
    }
}
