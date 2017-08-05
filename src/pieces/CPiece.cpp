#include "CPiece.h"


void CPiece::setCoordinates (int cordXI, int cordYI) {
  cordX = cordXI;
  cordY = cordYI;
}

bool CPiece::getColor() {
  return (color);
}

bool CPiece::isOutOfBoard (int cordX,int cordY) {
  if (cordX > 8 || cordY > 8) {
    return true;
  }
}

std::vector<std::string> CPiece::getMoves() {

}
