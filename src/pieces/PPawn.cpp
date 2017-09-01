#include "PPawn.h"
#include "../CPos.h"

PPawn::PPawn(bool colorI, CPos* currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PPawn::~PPawn()
{
    //dtor
}


std::vector<std::string> PPawn::getMoves() {
  tempMoves.clear();
  //The moves are hardcoded, as they are constant for a King. PLEASE FORGIVE ME FOR THIS MADNESS!!!
  std::cout << pos->getPlayerColor() << "LOL" << std::endl;
  if (pos->getPlayerColor() == false) { //black
    /*black*/
    if (cordsInBounds (cordX, cordY-1)) {
      if ( squareAvailable (cordX, cordY-1)) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1));
      }
    }
    if (cordsInBounds (cordX, cordY -2) && cordY == 7) {
      if (squareAvailable (cordX, cordY+1) && squareAvailable (cordX, cordY+2)) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-2));
      }
    }

    if (cordsInBounds(cordX+1, cordY-1) && pos->getSquarePointer(cordX+1, cordY-1)->containsPiece()) {
      if (pos->getSquarePointer(cordX+1, cordY-1)->getPiecePointer()->getColor() != this-> color) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX +1, cordY-1));
      }
    }
    if (cordsInBounds(cordX-1, cordY-1) && pos->getSquarePointer(cordX-1, cordY-1)->containsPiece()) {
      if ((pos->getSquarePointer(cordX-1, cordY-1)->getPiecePointer()->getColor() != this-> color)) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
      }
    }
  } else {
    /*white*/
  }
  std::cout << "pawngeneration finished" << std::endl;
  return tempMoves;
}


bool PPawn::cordsInBounds (int cordXI,int cordYI) {
  bool result = true;
  if (((cordXI > 8) or (cordYI > 8)) or ((cordYI < 1) or (cordXI < 1))) {
    return false;
  }
}

bool PPawn::squareAvailable (int cordXI, int cordYI) {
  CSquare* searchedSquare;
  CPiece* searchedPiece;
  searchedSquare = pos->getSquarePointer (cordXI, cordYI);
  if (searchedSquare->containsPiece()) {
    return false;
  }
}
