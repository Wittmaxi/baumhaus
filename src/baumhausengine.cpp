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
    this->position = new CPos();
    this->init(); //might be not used... If so remove it. Initially used for debug
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
  this->color = false;
  position->feedFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
	firstTime = true;
}


void CBaumhausengine::analyzePos() {
	// TODO Main thinking logic would probably be here..
  std::string tempMove;
  if(firstTime) {
  }
  movesList.clear();
		std::vector<std::string> possibleMoves = position->getPossibleMoves(false); // TODO change the hardcoded 'false' to the actual current color
    if (possibleMoves.size() > 0) {
			movesList = possibleMoves;
      srand (time(NULL));
      tempMove = possibleMoves [rand() % possibleMoves.size()];
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
  pipe -> d ("THE BAUMHAUS-ENGINE WAS STARTED!");
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
          makeMove (pipe->dequeueInputMessage(true).substr(1, 4));
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

}

void CBaumhausengine::pong(std::string val) {
	pipe->queueOutputMessage("pong " + val);
}

void CBaumhausengine::makeMove(std::string move) {
  //remove the old piece pointer and set it otherwhere.
    movePointers (move);
    // update position to reflect move
    if (this->colorOnTurn == color) {pipe->queueOutputMessage("move " + move);} //output the current move
    this->colorOnTurn = !this->colorOnTurn; //change the player color
}

bool CBaumhausengine::movePointers (std::string move) {
  pipe -> d(move);
  std::vector<int> moveStartField = CPos::coordFromName (move.substr (0, 2));
  std::vector<int> moveEndField = CPos::coordFromName (move.substr (2, 2));

  CSquare* startSquare = position->getSquarePointer (moveStartField [0], moveStartField[1]);;
  CSquare* endSquare = position -> getSquarePointer (moveEndField[0], moveEndField[1]);

  if (startSquare->containsPiece() == false)  {return false;} // if there is no piece in the start square, return an error

  if (startSquare->getPiecePointer()->getColor() == this-> colorOnTurn) {
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          if (endSquare->getPiecePointer()->getColor() == this-> colorOnTurn) { //checks if the piece is of the same color
              return false;
          } else {
              pipe -> d ("taking some piece");
              endSquare->takePiece();
              endSquare->setPiecePointer(startSquare->removePiece());
          }
      } else {
          pipe -> d ("moving piece");
          endSquare->setPiecePointer (startSquare->removePiece());
      }
    } else {
      return false;
    }
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        std::cout << position->getSquarePointer (i+1, j+1)->containsPiece() << " ";
        }
        std::cout << std::endl;
    }

}
