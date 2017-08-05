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
  if (!(isOutOfBoard (cordX +1, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+1));
  }
  if (!(isOutOfBoard (cordX, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+1));
  }
  if (!(isOutOfBoard (cordX -1, cordY+1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX -1, cordY+1));
  }
  if (!(isOutOfBoard (cordX +1, cordY))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY));
  }
  if (!(isOutOfBoard (cordX -1, cordY))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY));
  }
  if (!(isOutOfBoard (cordX +1, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (!(isOutOfBoard (cordX, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
  }
  if (!(isOutOfBoard (cordX -1, cordY-1))) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
  }
}
