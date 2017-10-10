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
  if (hasPiece) {
    delete contained;
  }
}

CSquare::CSquare(const CSquare& other) {
  this->hasPiece = other.hasPiece;
  this->protection = other.protection;
  this->x = other.x;
  this->y = other.y;
  // if there is a piece on this square, clone it.
  if(other.hasPiece) {
    this->contained = other.contained->clone();
  }
}

CPiece* CSquare::removePiece() { //gives back a pointer to the piece so the engine can put it on another CSquare
  hasPiece = false;
  return contained;
}

void CSquare::takePiece() {
  if (hasPiece) { //if there is a piece, THEN ONLY delete the current piece
    delete contained; // deletes the instance of that piece.
    hasPiece = false;
  }
}

void CSquare::setPiecePointer (CPiece* input) { //gets the piece pointer as input
  contained = input;
  pipe->d("1");
  hasPiece = true;
  pipe->d(2);
  contained -> setCoordinates(this->x, this->y);
  pipe->d(3);
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

