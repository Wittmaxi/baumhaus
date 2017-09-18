#include "PPawn.h"
#include "../CPipe.h"
#include "../CPos.h"

CPiece* PPawn::clone(CPos* position) {
  CPiece* clone = new PPawn(this->color, position);

  return clone;
}

PPawn::PPawn(bool colorI, CPos* currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
    if (color) { //if the piece is white, give it a white FEN-Name
      fenType = 'P';
    } else {
      fenType = 'p';
    }
}

PPawn::~PPawn()
{
    //dtor
}


std::vector<std::string> PPawn::getMoves() {
  tempMoves.clear();
  //the flag "MO" added to is to signal, that the piece cant take to that direction. Is important when generating attack states of
  //squares.
  if (this->color == false) { //black
    if (squareAvailable (cordX, cordY-1)) { //single step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1) + "MO");
    }
    if (cordY == 7 && (squareAvailable (cordX, cordY-1) && squareAvailable (cordX, cordY -2))) { // double step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-2) + "MO");
    }
    if (cordsInBounds(cordX-1, cordY-1) && pos->getSquarePointer (cordX-1, cordY-1)-> containsPiece()) {
      if (pos->getSquarePointer (cordX-1, cordY-1)-> getPiecePointer()-> getColor() != this->color){
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
      }
    }
    if (cordsInBounds(cordX+1, cordY-1) && pos->getSquarePointer (cordX+1, cordY-1)-> containsPiece()) {
      if (pos->getSquarePointer (cordX+1, cordY-1)-> getPiecePointer()-> getColor() != this->color) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY-1));
      }
    }
  } else {
    if (squareAvailable (cordX, cordY+1)) { //single step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+1) + "MO");
    }
    if (cordY == 2 && (squareAvailable (cordX, cordY+1) && squareAvailable (cordX, cordY +2))) { // double step
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY+2) + "MO");
    }
    if (cordsInBounds(cordX-1, cordY+1) && pos->getSquarePointer (cordX-1, cordY+1)-> containsPiece()) {
      if (pos->getSquarePointer (cordX-1, cordY+1)-> getPiecePointer()-> getColor() != this->color){
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY+1));
      }
    }
    if (cordsInBounds(cordX+1, cordY+1) && pos->getSquarePointer (cordX+1, cordY+1)-> containsPiece()) {
      if (pos->getSquarePointer (cordX+1, cordY+1)-> getPiecePointer()-> getColor() != this->color) {
        tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX+1, cordY+1));
      }
    } 
  }
  return tempMoves;
}


bool PPawn::cordsInBounds (int cordXI,int cordYI) {
  if (((cordXI > 8) || (cordYI > 8)) || ((cordYI < 1) || (cordXI < 1))) {
    return false;
  }
  return true;
}

bool PPawn::squareAvailable (int cordXI, int cordYI) {
  if (pos->getSquarePointer (cordXI, cordYI) -> containsPiece() || !(cordsInBounds (cordXI, cordXI))) {
    return false;
  }
  return true;
}
