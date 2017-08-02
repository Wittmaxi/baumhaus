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

void CSquare::setPiece (char fenName) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"
  switch (fenName) {
    //white pieces
      case 'K': break;//king
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
