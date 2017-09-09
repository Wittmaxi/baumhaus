#include "PQueen.h"
#include "../CPipe.h"
#include "../CPos.h"

PQueen::PQueen(bool colorI, CPos *currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PQueen::~PQueen()
{
    //dtor
}



std::vector<std::string> PQueen::getMoves() {
  tempMoves.clear();

  bool collided = false;
  int relPosX = cordX; // where the move generator currently is.
  int relPosY = cordY;
  //four directions
  //top-left:
  while (collided == false) {
    relPosY +=1;
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
    //top-right:
  while (collided == false) {
    relPosY +=1;
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
    //bottom-right:
  while (collided == false) {
    relPosX += 1;
    relPosY -= 1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  collided = false;
  relPosY = cordY;
  relPosX = cordX;
    //bottom-left:
  while (collided == false) {
    relPosY -=1;
    relPosX -= 1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
  }
  while (collided == false) {
    relPosY +=1;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
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

bool PQueen::squareAvailable (int cordXI,int cordYI) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  if (((cordXI > 8) || (cordYI > 8)) || ((cordYI < 1) || (cordXI < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = this-> pos -> getSquarePointer (cordXI, cordYI);
    if (currentSquare -> containsPiece() == true) {
      currentPiece = currentSquare -> getPiecePointer();
      if (currentPiece->getColor() == this->getColor()) {
        result = false;
      } else {
              tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(cordXI, cordYI));
              result = false;
      }
    }
  }
  return result;
}
