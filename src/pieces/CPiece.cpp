#include "CPiece.h"


void CPiece::setCoordinates (int cordXI, int cordYI) { // NO ZERO INDEXING!
  cordX = cordXI;
  cordY = cordYI;
}

bool CPiece::getColor() {
  return this->color;
}
