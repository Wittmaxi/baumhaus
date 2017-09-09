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

void CSquare::setPiecePointer (CPiece* input) { //gets the piece pointer as input and the type of the piece.
  contained = input;
  hasPiece = true;
  contained -> setCoordinates(x, y);
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

int CSquare::getWhiteAttackers() {
  return whiteAttackers;
}

int CSquare::getBlackAttackers() {
    return blackAttackers;
}

void CSquare::addAttackers(bool color) {
  if (color) { //add white attacker
    whiteAttackers ++;
  } else { // add black attacker
    blackAttackers ++;
  }
  calcTotalAttack();
}

int CSquare::calcTotalAttack() {
  totalAttack = whiteAttackers - blackAttackers; // minus for black
  return totalAttack;
}

int CSquare::returnAttackState() {
  return totalAttack;
}
