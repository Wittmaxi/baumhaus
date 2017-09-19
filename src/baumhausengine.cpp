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
  // TODO NOW
  // enter 'force' mode
  // stop clocks
  // reset time controls
  // reset depth limits
  // use wall clock
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
  if(firstTime) {
	pipe->d("First Time");
  }
  movesList.clear();
		std::vector<std::string> possibleMoves = position->getPossibleMoves(false); // TODO change the hardcoded 'false' to the actual current color
    if (possibleMoves.size() > 0) {
			movesList = possibleMoves;
      pipe->d("setting seed");
      srand (time(NULL));
      tempMove = possibleMoves [rand() % possibleMoves.size()];
      pipe->d("temp move: " + tempMove);
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
    		else if("usermove" == message) { //quick and dirty way. needs to be made better
			    
          auto move = pipe->dequeueInputMessage(true);
          
          // TODO: validate move before determining that this should happen.
          // If not a valid move, we must throw an error and not do anything.

          movePointers(move);
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
        else if("go" == message) {
          go();
        }
        else if ("playOther" == message) {
          playOther();
        }
        else if("white" == message) {
          this->color = false; // opponent is white, so engine is black
          // TODO stop clocks
        }
        else if ("black" == message) {
          this->color = true; // opponent is black, so engine is white
          // TODO stop clocks
        }
	}

	pipe->d("Goodbye!");
}

void CBaumhausengine::pong(std::string val) {
	pipe->queueOutputMessage("pong " + val);
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
  pipe->d("in movePointers_" + move);
  pipe->d("no return type");
  std::vector<int> moveStartField = CPos::coordFromName (move.substr (0, 2));
  pipe->d("cord 1");
  std::vector<int> moveEndField = CPos::coordFromName (move.substr (2, 2));
  pipe->d("cord 2");

  pipe->d("declaring vars " + str(moveStartField[0]) + " " + str(moveStartField[1]));
  CSquare* startSquare = position->getSquarePointer (moveStartField [0], moveStartField[1]);
  pipe->d("declared variable 1! " + str(moveStartField[0]) + " " + str(moveStartField[1]));
  CSquare* endSquare = position -> getSquarePointer (moveEndField[0], moveEndField[1]);
  pipe->d("declared variables!");

  if (startSquare->containsPiece() == false)  {return false;} // if there is no piece in the start square, return an error

  pipe->d("to play: " + str(this->colorOnTurn) + " " + str(startSquare->getPiecePointer()->getColor()));
  if (startSquare->getPiecePointer()->getColor() == this-> colorOnTurn) {
      pipe->d("pointer is correct");
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          pipe->d("contains piece");
          if (endSquare->getPiecePointer()->getColor() == this-> colorOnTurn) { //checks if the piece is of the same color
              return false;
              pipe->d("error");
          } else {
              pipe->d("taking enemy piece");
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

void CBaumhausengine::go() {
  // TODO: once force-mode is implemented, exit force mode here, start clock
  this->color = this->colorOnTurn;
}

void CBaumhausengine::playOther() {
  // TODO: similar to go(). exit force mode, enter pondering, and start opponent's clock.
  this->color = !this->colorOnTurn;

}
