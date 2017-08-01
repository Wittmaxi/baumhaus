#include "CPos.h"

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

std::string CPos::getSquareName(int x, int y) {

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

std::vector <std::vector <std::string>> CPos::getPossibleMoves (bool color) {

}

void CPos::loopPieces(){
  CSquare *currentSquare;
  for (int x=1; x++; x=64) {
    for (int y=1; y++; y=64) {
      currentSquare = getSquarePointer(x, y);
      if (currentSquare->containsPiece()) {

      }
    }
  }
}
