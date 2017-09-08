#include "CDummyPiece.h"
#include "../CPipe.h"
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
  pipe->d("dummymovesCalled");
  return tempMoves;
}

bool CDp::squareAvailable (int cordX,int cordY) {

}
