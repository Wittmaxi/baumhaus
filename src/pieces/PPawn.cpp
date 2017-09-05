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
    std::cout << cordX << cordY << std::endl;
    if (squareAvailable (cordX, cordY-1)) { //single step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1));
    }
    if (cordY == 7 && (squareAvailable (cordX, cordY-1) && squareAvailable (cordX, cordY -2))) { // double step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-2));
    }
  } else {
    /*white*/
  }
  std::cout << "pawngeneration finished" << tempMoves.size() << std::endl;
  return tempMoves;
}


bool PPawn::cordsInBounds (int cordXI,int cordYI) {
  if (((cordXI > 8) or (cordYI > 8)) or ((cordYI < 1) or (cordXI < 1))) {
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
