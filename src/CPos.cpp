#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"
#include "pieces/CDummyPiece.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{

  std::vector<CSquare*> row;
  int x = 1;
  for (x=1; x <= 8; x++) {
      squares.push_back (row);
    }
    for (int y=1; y <= 8; y++) {
        for (int x=1; x <= 8; x++) { //loops through the entire board
          squares[x-1, y-1].push_back (new CSquare(x, y));
        }
    }

}

CPos::~CPos()
{
    //dtor
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"
  if (fenName == 'N') {
    currentSquarePointer -> setPiecePointer (new CDp(false, this));
  } else {
    currentSquarePointer -> setPiecePointer(new PKing(false, this));
  };
  /*switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer(new PKing(true, this));break;//king
      case 'N': break; //knight
      case 'R': break; //rook
      case 'B': break; //bishop
      case 'P': break; //pawn
      case 'Q': break; //queen
    //black pieces
      case 'k': currentSquarePointer -> setPiecePointer(new PKing(false, this)); break; //king
      case 'r': break; //rook
      case 'n': break; //knight
      case 'b': break; //bishop
      case 'p': break; //pawn
      case 'q': break; //queen

  } */
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::string currentName;
  currentName = fileNames[x-1] + std::to_string(y);
  std::cout << currentName << std::endl;
  return (currentName);
}

std::vector <int> CPos::coordFromName (std::string squareName) {
  if (squareName.size() > 2) {
    std::cout << "Error in square Name conversion" << std::endl;
  } else {
    //ok, this is messy, but: we take the character value of the squares character and remove what is before A
    std::vector <int> returnVector;
    returnVector.push_back (squareName [0] -96);
    returnVector.push_back (squareName [1] -48);
    return returnVector;
  }
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
    parseFen(fenI);
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.
  setPiece ('k', getSquarePointer(8, 5)); //hardcoding some pieces in for the time-being
  setPiece ('N', getSquarePointer(8, 6));
  setPiece ('N', getSquarePointer(7, 6));
  setPiece ('N', getSquarePointer(7, 4));
  setPiece ('N', getSquarePointer(8, 4));
  setPiece ('N', getSquarePointer(5, 5)); // that one pawn the engine moves at the beginning
}

CSquare* CPos::getSquarePointer (int x, int y) {
  return squares[x-1][y-1];
}

std::vector <std::string> CPos::getPossibleMoves (bool color) {
  moves.clear();
  loopPieces();
  return moves;
}

void CPos::loopPieces(){
  CSquare *currentSquare;
  CPiece *currentPiece;
  for (int x=1; x<= 8; x++) {
		for (int y=1; y <= 8; y++) { //loops through the entire board
			currentSquare = getSquarePointer(x, y);
			if (currentSquare->containsPiece()) { //if the square contains a piece
        std::cout << x << y << "contains a piece" << std::endl;
				currentPiece = currentSquare->getPiecePointer();
				if (toPlay == true) { //white to play
					if (currentPiece->getColor() == true) { //if the piece is white and white is to play
            appendMoves(currentPiece -> getMoves());
					}
				}
				else { //black to play
					std::cout << currentPiece -> getColor () << std::endl;
					if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
            appendMoves(currentPiece -> getMoves());
            std::cout << "moves got" << std::endl;
					}
				}
			}
		}
	}
}

void CPos::appendMoves(std::vector <std::string> newMoves) { //appends moves of a single piece to the entire list of Moves.
if (newMoves.size() > 0) {
    moves.insert(moves.end(), newMoves.begin(), newMoves.end());
  }
}
