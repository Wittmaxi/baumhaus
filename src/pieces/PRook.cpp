#include "PRook.h"
#include "../CPipe.h"
#include "../CPos.h"

PRook::PRook(bool colorI)
{
    //ctor
    color = colorI;
}

PRook::~PRook()
{
    //dtor
}

PRook::PRook(const PRook& other) {
  this->color = other.color;
  this->cordX = other.cordX;
  this->cordY = other.cordY;
}

CPiece* PRook::clone() {
  return new PRook(*this);
}

std::vector<std::string> PRook::getMoves(CPos* currentPos) {
  this->pos = currentPos;
  tempMoves.clear();
  pipe->d("Rook getMoves");
  bool collided = false;
  int relPosX = cordX; // where the move generator currently is.
  int relPosY = cordY;
  //four directions
  //top:
  while (collided == false) {
    relPosY +=1;
    pipe->d("top-left");
    if (squareAvailable (relPosX, relPosY)) {
      pipe->d("if");
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      pipe->d("else");
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  collided = false;
  relPosY = cordY;
  relPosX = cordX;
  //right
  while (collided == false) {
    relPosX += 1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  collided = false;
  relPosY = cordY;
  relPosX = cordX;
    //left:
  while (collided == false) {
    relPosX -= 1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  collided = false;
  relPosY = cordY;
  relPosX = cordX;
    //bottom:
  while (collided == false) {
    relPosY -=1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  return tempMoves;
}

bool PRook::squareAvailable (int cordXI,int cordYI) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  if (((cordXI > 8) || (cordYI > 8)) || ((cordYI < 1) || (cordXI < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordXI, cordYI);
    if (currentSquare -> containsPiece() == true) {
      pipe->d("found square containing a piece");
      currentPiece = currentSquare -> getPiecePointer();
      pipe->d(str(currentPiece->getColor()) + ", " + str(this->getColor()));
      if (currentPiece->getColor() == this->getColor()) {
        pipe->d("returned false");
        result = false;
      } else {
              tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(cordXI, cordYI));
              result = false;
      }
    }
  }
  return result;
}
