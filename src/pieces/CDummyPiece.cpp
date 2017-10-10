#include "CDummyPiece.h"
#include "../CPipe.h"
#include "../CPos.h"


CDp::CDp(bool colorI)
{
    //ctor
    color = colorI; 
    if (color) { //if the piece is white, give it a white FEN-Name
      fenType = 'D';
    }
    else {
      fenType = 'd';
    }
}

CDp::~CDp()
{
    //dtor
}

CDp::CDp(const CDp& other) {
  this->color = other.color;
  this->cordX = other.cordX;
  this->cordY = other.cordY;
  this->fenType = other.fenType;
}

CPiece* CDp::clone() {
  return new CDp(*this);
}

std::vector<std::string> CDp::getMoves(CPos* currentPos) {
  this->pos = currentPos;
  std::vector <std::string> tempMoves;
  return tempMoves;
}

bool CDp::squareAvailable (int cordX,int cordY) {

}
