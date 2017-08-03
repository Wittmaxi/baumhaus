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
  std::vector <std::string> moves;
  //The moves are hardcoded, as they are constant for a King.

}
