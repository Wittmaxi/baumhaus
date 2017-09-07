#include "CDummyPiece.h"
#include "../CPos.h"

CDp::CDp(bool colorI, CPos *currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

CDp::~CDp()
{
    //dtor
}

std::vector<std::string> CDp::getMoves() {
  std::vector <std::string> tempMoves;
  std::cout << "dummymovesCalled" << std::endl;
  return tempMoves;
}

bool CDp::squareAvailable (int cordX,int cordY) {

}
