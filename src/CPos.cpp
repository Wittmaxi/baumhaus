#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"
#include "pieces/CDummyPiece.h"
#include "pieces/PBishop.h"
#include "pieces/PRook.h"
#include "pieces/PKnight.h"
#include "pieces/PPawn.h"
#include "pieces/PQueen.h"
#include "CPipe.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos() //the constructor of the position. Initializes the array of CSquares.
{

  std::vector<CSquare*> row; //an empty row that will be pushed back
  for (x=1; x <= 8; x++) { //create Rows inside the array of squares
    squares.push_back (row);
  }

  for (int y=1; y <= 8; y++) { // loop through the entire array
    for (int x=1; x <= 8; x++) { //loops through the entire board
      squares[y-1]. push_back (new CSquare(x, y)); //create squares in those Rows
    }
  }
}

CPos::CPos (CPos* copy) { //copy constructor. Creates the vector of Squares and then take the fen of the old position
  std::vector<CSquare*> row;  //create an empty row

  for (x=1; x <= 8; x++) {
    squares.push_back (row); //create rows inside of the array
  }

  for (int y=1; y <= 8; y++) {
    for (int x=1; x <= 8; x++) { //loops through the entire board
      squares[y-1]. push_back (new CSquare(x, y)); //creates square in the rows
    }
  }

  this->toPlay = copy->toPlay; //copy the player color
  this->fen (copy->getFen); //copies the fen of the old class
  this->feedFen(this->fen); //place pieces according to the FEN

}

CPos::~CPos() //destructor
{
    //dtor
  for (int y=1; y <= 8; y++) {
    for (int x=1; x <= 8; x++) { //loops through the entire board
      delete squares [x-1][y-1];  //delete the instances of CSquare
    }
  }
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"
  switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer (new PKing(true, this)); break;//king
      case 'N': currentSquarePointer -> setPiecePointer (new PKnight(true, this)); break; //knight
      case 'R': currentSquarePointer -> setPiecePointer (new PRook(true, this)); break; //rook
      case 'B': currentSquarePointer -> setPiecePointer (new PBishop(true, this)); break; //bishop
      case 'P': currentSquarePointer -> setPiecePointer (new PPawn(true, this));break; //pawn
      case 'Q': currentSquarePointer -> setPiecePointer (new PQueen(true, this)); break; //queen
      case 'D': currentSquarePointer -> setPiecePointer (new CDp(true, this)); break; //dummy piece
    //black pieces
      case 'k': currentSquarePointer -> setPiecePointer (new PKing(false, this)); break; //king
      case 'r': currentSquarePointer -> setPiecePointer (new PRook(false, this));break; //rook
      case 'n': currentSquarePointer -> setPiecePointer (new PKnight(false, this)); break; //knight
      case 'b': currentSquarePointer -> setPiecePointer (new PBishop(false, this)); break; //bishop
      case 'p': currentSquarePointer -> setPiecePointer (new PPawn(false, this));break; //pawn
      case 'q': currentSquarePointer -> setPiecePointer (new PQueen(false, this)); break; //queen
      case 'd': currentSquarePointer -> setPiecePointer (new CDp(false, this)); break; //dummy piece
  }
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}; //create an array with the possible denominations of files
  return (fileNames[x-1] + std::to_string(y));
}

std::vector <int> CPos::coordFromName (std::string squareName) { //return two nummeral values from the algebraic notation for a square
  if (squareName.size() > 2) { //look if the square name is of the correct length
    pipe->d("Error in square Name conversion");
  } else {
    std::vector <int> returnVector;
    //get the nummeral values of both elements of the square names
    returnVector.push_back (squareName [0] -96); //-96 for the character (a = 97)
    returnVector.push_back (squareName [1] -48); //-48 for the number
    return returnVector;
  }
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
    parseFen(fenI);
}

void CPos::parseFen (std::string fen) { //parses a fen and sets pieces onto the board accordingly
  int rowCounter; //what row we are in
  int columnCounter; //what column we are in

  for (int i = 0; i < fen.size(); i++) { //go trough the entire text
    char currentChar = fen[i]; //what the current character is

    if (std::isDigit(currentChar)) { //if the current character is a number (number = number of free squares)
      columnCounter += character - 48; //add the column counter if some squares are let out
    } else if (currentChar == '/') { //new row
      rowCounter++; //increment the row counter
      columnCounter = 0; //reset the column counter
    } else if (currentChar == ' ') { //if the character is empty (relevant part of the fen is finished)
        break; //simply break out of the loop
    } else {
      setPiece (currentChar, getSquarePointer(columnCounter, rowCounter)); //if the character is a text, put an according piece onto the correct row/column
    }

  }
}

std::string CPos::getFen () { //returns the current FEN
  return fen;
}

CSquare* CPos::getSquarePointer (int x, int y) { //returns the pointer of the square on x, y
  return squares[y-1][x-1];
}

std::vector <std::string> CPos::getPossibleMoves (bool colorI) { //returns the possible moves for the side colorI
  moves.clear(); //remove the moves that might already have been generated
  moves = loopPieces(colorI); //find every legal move (No matter if its good or bad)

  return moves; //return the generated moves
}

std::vector<std::string> CPos::loopPieces(bool colorI){ //returns every legal move
  CSquare *currentSquare; //create empty pointer for the square the loop is currently in. Gets updated every iteration
  CPiece *currentPiece; //pointer to the current piece. Is updated on every iteration of the loop
  std::vector<std::string> tempMoves; //temp array to store moves

  for (int x=1; x<= 8; x++) {
		for (int y=1; y <= 8; y++) { //loops through the entire board
			currentSquare = getSquarePointer(x, y); //get the pointer to the current square

      if (currentSquare->containsPiece()) { //if the square contains a piece
				currentPiece = currentSquare->getPiecePointer(); //if the current square has a piece, then get its piece pointer

				if (colorI) { //white to play
					if (currentPiece->getColor() == true) { //if the piece is white and white is to play
            tempMoves += currentPiece -> getMoves();
					}
				} else { //black to play
					if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
            tempMoves += currentPiece -> getMoves();
					}
				}
			}
		}
	}
  return tempMoves;
}

bool CPos::getPlayerColor () { //returns the color of the current player
  return toPlay;
}

bool CPos::kingIsInCheck(bool colorI) { //returns, wether the king that is to play is in check
  std::pair <int, int> tmp; //makes a temporary pair
  tmp = getKingCoords(colorI); //get the coordinates into the pair

  CSquare* currentSquare =  getSquarePointer (std::get<0> (tmp), std::get<1> (tmp)); //get the square the King is on

  /*

  NEEDS REWRITING, NEEDS REWRITING, NEEDS REWRITING

  */

}

std::pair<int, int> CPos::getKingCoords(bool colorI) { //get the coordinates of the king of colorI and return a pair with its coordinates
  CSquare* currentSquare;
  CPiece* currentPiece;

  for (int x = 0; x < 8; x++) { //go trough every square and check if a king of the correct color is on it
    for (int y = 0; y < 8; y++) {
      currentSquare = getSquarePointer(x+1, y+1); //get the pointer to the currently used square

      if (currentSquare->containsPiece()) { //if the current square contains a piece
        currentPiece = currentSquare-> getPiecePointer (); //get the piece pointer of the current piece

        if ((currentPiece->getPieceType() == 'K' && colorI == true) || (currentPiece->getPieceType() == 'k' && colorI == false)) { // if the piece is the same as the current player color
          std::pair<int, int> tmp = std::make_pair (x, y); //make a pair with the coordinates of the currentSquare
          //(square where the King is)

          return tmp; //return the std::Pair
        }
      }
    }
  }

  std::pair<int, int> tmp = std::make_pair (-1, -1); //edge-case //if there is no king, return -1, -1
  return tmp;
}


std::vector <std::string> CPos::getOutOfCheck(std::vector <std::string> movesI, bool colorI) {

  std::pair <int, int> temp = getKingCoords(colorI); //get the coordinates of the according King
  std::vector <std::string> newMoves; //create a new array to store the legal moves
  

  /*

    NEEDS REWRITING, NEEDS REWRITING, NEEDS REWRITING, NEEDS REWRITING
  
  */
}

bool CPos::movePointers (std::string move) { //move the piece pointers, after a move
  std::vector<int> moveStartField = coordFromName (move.substr (0, 2)); //get the field where the piece started
  std::vector<int> moveEndField = coordFromName (move.substr (2, 2)); //get the field the piece moves onto

  CSquare* startSquare = this-> getSquarePointer (moveStartField [0], moveStartField[1]); //the square-pointer where the piece starts
  CSquare* endSquare = this-> getSquarePointer (moveEndField[0], moveEndField[1]); //the square where the piece ends

  if (startSquare->containsPiece() == false)  {
    return false;
  } // if there is no piece in the start square, return an error

  if (startSquare->getPiecePointer()->getColor() == this-> toPlay) {
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          if (endSquare->getPiecePointer()->getColor() == this-> toPlay) { //checks if the piece is of the same color
              return false;
          } else {
              pipe-> d("Taking a piece");
              endSquare->takePiece();
              endSquare->setPiecePointer(startSquare->removePiece());
          }
      } else {
          pipe-> d("movind a piece");
          endSquare->setPiecePointer (startSquare->removePiece());
      }
    } else {
      return false;
    }
}

void CPos::writeBitBoard() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      pipe -> d(getSquarePointer(x+1, y+1)->containsPiece(), false, false);
    }
    pipe->d("");
  }
}

void CPos::setColor(bool colorI) {
  toPlay = colorI;
}

void CPos::updateFen () {
  std::string tempFen;
  for (int i = 0; i < squares.size(); i++) {
    for (int j = 0; j < squares[i].size();j++) {

    }
  }
}
