#include "CSquare.h"
#include "CPipe.h"
#include "iostream"
//include all of the piece-files

#include "pieces/PKing.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CSquare::CSquare(int iX, int iY)
{
    //ctor
    hasPiece = false;
    x = iX;
    y = iY;
}

CSquare::~CSquare()
{
    //dtor
    if (hasPiece) { //delete the pointed piece
      delete contained;
    }
}

CPiece* CSquare::removePiece() { //gives back a pointer to the piece so the engine can put it on another CSquare
  hasPiece = false;
  return contained;
}

void CSquare::takePiece() {
  delete contained; // deletes the instance of that piece.
  hasPiece = false;
}

void CSquare::setPiecePointer (CPiece* input) {
  contained = input;
  hasPiece = true;
  pipe->d("set hasPiece to true ");
  contained -> setCoordinates(x, y);
}


//attack state
void CSquare::addBlackAttacker () {
    protection -= 1;
}

void CSquare::addWhiteAttacker() {
   protection += 1;
}

int CSquare::returnAttackState() {
  return protection;
}

bool CSquare::containsPiece() {
  return hasPiece;
}

CPiece *CSquare::getPiecePointer() {
  if (!(containsPiece())) {

  } else {
      return (contained);
  }
}
