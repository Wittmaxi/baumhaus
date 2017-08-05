#include "PKing.h"
#include "../CPos.h"

PKing::PKing(bool colorI, CPos *currentPosition /*true: white*/)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PKing::~PKing()
{
    //dtor
}

std::vector<std::string> PKing::getMoves() {
  std::vector <std::string> tempMoves;
  //The moves are hardcoded, as they are constant for a King.
  if (!(squareAvailable (cordX +1, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+1));
  }
  if (!(squareAvailable (cordX, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+1));
  }
  if (!(squareAvailable (cordX -1, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX -1, cordY+1));
  }
  if (!(squareAvailable (cordX +1, cordY))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY));
  }
  if (!(squareAvailable (cordX -1, cordY))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY));
  }
  if (!(squareAvailable (cordX +1, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (!(squareAvailable (cordX, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (!(squareAvailable (cordX -1, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
  }
}

bool PKing::squareAvailable (int cordX,int cordY) {
  bool result;
  if (cordX > 8 || cordY > 8) {
    result = true;
  }
  if (!(pos->getSquarePointer(cordX, cordY)->getPiecePointer() -> getColor () == this->getColor())) { //checks if there is a piece of the own type.
    result = false;
  }
  return result;
}
