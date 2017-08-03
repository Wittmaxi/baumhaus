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

CSquare::CSquare()
{
    //ctor
}

CSquare::~CSquare()
{
    //dtor
}

CPiece* CSquare::removePiece() { //gives back a pointer to the piece so the engine can put it on another CSquare
  return contained;
  contained = NULL;
}

void CSquare::takePiece() {
  delete contained; // deletes the instance of that piece.
}

void CSquare::setPiecePointer (CPiece* input) {
  contained = input;
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
  if (contained == NULL) {
    return (false);
  } else {
    return (true);
  }
}

CPiece *CSquare::getPiecePointer() {
  if (contained == NULL) {
    std::cout<<"ERROR: A piece was queried, but there is no piece on the current square. This message is only meant to be seen for debug purposes." << std::endl;
  } else {
      return (contained);
  }
}
