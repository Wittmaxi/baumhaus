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
  std::cout << "getMovesDebug 1" << std::endl;
  std::cout << "coordX=" << cordX << ", coordY=" << cordY << std::endl;
  std::vector <std::string> tempMoves;
  //The moves are hardcoded, as they are constant for a King. PLEASE FORGIVE ME FOR THIS MADNESS!!!
  if (squareAvailable (cordX +1, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+1));
  }
  if (squareAvailable (cordX, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+1));
  }
  if (squareAvailable (cordX -1, cordY+1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX -1, cordY+1));
  }
  if (squareAvailable (cordX +1, cordY)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY));
  }
  if (squareAvailable (cordX -1, cordY)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY));
  }
  if (squareAvailable (cordX +1, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (squareAvailable (cordX, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (squareAvailable (cordX -1, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
  }
  std::cout << "getMovesDebug 3" << std::endl;
  return tempMoves;
}

bool PKing::squareAvailable (int cordX,int cordY) {
  bool result;
  if (cordX <= 8 and cordY <= 8) {
    result = false;
  }else if (!(pos->getSquarePointer(cordX, cordY)->getPiecePointer() -> getColor () == this->getColor())) { //checks if there is a piece of the own type.
    result = false;
  }
  return result;
}
