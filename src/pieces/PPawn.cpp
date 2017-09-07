#include "PPawn.h"
#include "../CPipe.h"
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
  if (pos->getPlayerColor() == false) { //black
	pipe->d(str(cordX) + ", " + str(cordY));
    if (squareAvailable (cordX, cordY-1)) { //single step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1));
    }
    if (cordY == 7 && (squareAvailable (cordX, cordY-1) && squareAvailable (cordX, cordY -2))) { // double step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-2));
    }
  } else {
    /*white*/
  }
  pipe->d("pawngeneration finished" + str(tempMoves.size()));
  return tempMoves;
}


bool PPawn::cordsInBounds (int cordXI,int cordYI) {
  if (((cordXI > 8) || (cordYI > 8)) || ((cordYI < 1) || (cordXI < 1))) {
    return false;
  }
  return true;
}

bool PPawn::squareAvailable (int cordXI, int cordYI) {
  if (pos->getSquarePointer (cordXI, cordYI) -> containsPiece() && !(cordsInBounds (cordXI, cordXI))) {
    return false;
  }
  return true;
}
