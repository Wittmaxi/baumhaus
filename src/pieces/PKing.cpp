#include "PKing.h"
#include "../CPipe.h"
#include "../CPos.h"

PKing::PKing(bool colorI)
{
    //ctor
    color = colorI;
    if (color) { //if the piece is white, give it a white FEN-Name
      fenType = 'K';
    } else {
      fenType = 'k';
    }
}

PKing::~PKing()
{
    //dtor
}

PKing::PKing(const PKing& other) {
  this->color = other.color;
  this->cordX = other.cordX;
  this->cordY = other.cordY;
  this->fenType = other.fenType;
}

CPiece* PKing::clone() {
  return new PKing(*this);
}

std::vector<std::string> PKing::getMoves(CPos* currentPos) {
  this->pos = currentPos;
  pipe->d("getMovesDebug 1");
  pipe->d("coordX= " + str(cordX) + "\tcoordY= " + str(cordY));
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
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX, cordY-1));
  }
  if (squareAvailable (cordX -1, cordY-1)) {
    tempMoves.push_back (CPos::getSquareName(cordX, cordY) + CPos::getSquareName(cordX-1, cordY-1));
  }
  return tempMoves;
}

bool PKing::squareAvailable (int cordX,int cordY) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  if (((cordX > 8) || (cordY > 8)) || ((cordY < 1) || (cordX < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordX, cordY);
    if (currentSquare -> containsPiece() == true) {
      currentPiece = currentSquare -> getPiecePointer();
      if (currentPiece->getColor() == this->getColor()) {
        result = false;
      }
    }
  }
  return result;
}
