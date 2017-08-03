#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{
    //ctor
}

CPos::~CPos()
{
    //dtor
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"
  switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer(new PKing(true, this));break;//king
      case 'N': break; //night
      case 'R': break; //rook
      case 'B': break; //bishop
      case 'P': break; //pawn
      case 'Q': break; //queen
    //black pieces
      case 'k': break; //king
      case 'r': break; //rook
      case 'n': break; //night
      case 'b': break; //bishop
      case 'p': break; //pawn
      case 'q': break; //queen

  }
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  return (fileNames[x], std::to_string(y));
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.
  while (true) { //nothingly nothingness.

  }
}

CSquare *CPos::getSquarePointer (int x, int y) {
  return &squares[x][y];
}

std::vector <std::string> CPos::getPossibleMoves (bool color) {

}

void CPos::loopPieces(){
  CSquare *currentSquare;
  CPiece *currentPiece;
  for (int x=1; x++; x=64) {
    for (int y=1; y++; y=64) { //loops through the entire board
        currentSquare = getSquarePointer(x, y);
        if (currentSquare->containsPiece()) { //if the square contains a piece
            currentPiece = currentSquare->getPiecePointer();
            if (toPlay == true) { //white to play
              if (currentPiece->getColor() == true) { //if the piece is white and white is to play
                  currentPiece -> getMoves();
              }
            } else //black to play
              {
                if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
                    //currentPiece -> getMoves();
                }
              }
        }
    }
  }
}

void CPos::appendMoves(std::vector <std::string> newMoves) { //appends moves of a single piece to the entire list of Moves.
    moves.insert(moves.end(), newMoves.begin(), newMoves.end());
}
