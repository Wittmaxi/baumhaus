#include "PRook.h"
#include "../CPos.h"

PRook::PRook(bool colorI, CPos *currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PRook::~PRook()
{
    //dtor
}



std::vector<std::string> PRook::getMoves() {
  tempMoves.clear();
  std::cout<< "bishop getMoves" << std::endl;
  bool collided = false;
  int relPosX = cordX; // where the move generator currently is.
  int relPosY = cordY;
  //four directions
  //top:
  while (collided == false) {
    relPosY +=1;
    std::cout << "top-left" << std::endl;
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

bool PRook::squareAvailable (int cordXI,int cordYI) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  if (((cordXI > 8) or (cordYI > 8)) or ((cordYI < 1) or (cordXI < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordXI, cordYI);
    if (currentSquare -> containsPiece() == true) {
      std::cout << "found square containing a piece" << std::endl;
      currentPiece = currentSquare -> getPiecePointer();
      std::cout << currentPiece->getColor () << this->getColor() << std::endl;
      if (currentPiece->getColor() == this->getColor()) {
        std::cout << "returned false" << std::endl;
        result = false;
      } else {
              tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(cordXI, cordYI));
              result = false;
      }
    }
  }
  return result;
}
