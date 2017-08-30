#include "PBishop.h"
#include "../CPos.h"

PBishop::PBishop(bool colorI, CPos *currentPosition)
{
    //ctor
    color = colorI;
    pos = currentPosition;
}

PBishop::~PBishop()
{
    //dtor
}

std::vector<std::string> PBishop::getMoves() {

  std::cout<< "bishop getMoves" << std::endl;
  std::vector <std::string> tempMoves;
  bool collided = false;
  int relPosX = cordX; // where the move generator currently is.
  int relPosY = cordY;
  //four directions
  //top-left:
  while (collided == false) {
    relPosY +=1;
    relPosX -= 1;
    std::cout << "top-left" << std::endl;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }

    if (pos->getSquarePointer (cordY, cordX) -> containsPiece()) {
      collided = true;
    }
  }
  collided = false;
    //top-right:
  while (collided == false) {
    relPosY +=1;
    relPosX += 1;
    std::cout << "top-right" << std::endl;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
      if (pos->getSquarePointer (cordY, cordX) -> containsPiece()) {
      collided = true;
    }
  }
  collided = false;
    //bottom-right:
  while (collided == false) {
    relPosX += 1;
    relPosY -= 1;
    std::cout << "bottom-right" << std::endl;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      std::cout << "stopped exec" << std::endl;
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
    if (pos->getSquarePointer (cordY, cordX) -> containsPiece()) {
      collided = true;
    }
  }
  std::cout << "exited bottom-right" << std::endl;
  collided = false;
    //bottom-left:
  while (collided == false) {
    relPosY -=1;
    relPosX -= 1;
    std::cout << "bottom-left" << std::endl;
    if (squareAvailable (relPosX, relPosY)) {
      tempMoves.push_back (CPos::getSquareName (cordX, cordY) + CPos::getSquareName(relPosX, relPosY));
    } else {
      collided = true; // just trying to go out the way of ANOTHER break xD
    }
    if (pos->getSquarePointer (cordY, cordX) -> containsPiece()) {
      collided = true;
    }
  }
  return tempMoves;
}

bool PBishop::squareAvailable (int cordX,int cordY) {
  bool result = true;
  CSquare* currentSquare;
  CPiece* currentPiece;
  std::cout << cordX << ", " << cordY << std::endl;
  if (((cordX > 8) or (cordY > 8)) or ((cordY < 1) or (cordX < 1))) {
    result = false;
  }else { //checks if there is a piece of the own type.
    currentSquare = pos -> getSquarePointer (cordY, cordX);
    if (currentSquare -> containsPiece() == true) {
      std::cout << "found square containing a piece" << std::endl;
      currentPiece = currentSquare -> getPiecePointer();
      std::cout << currentPiece->getColor () << this->getColor() << std::endl;
      if (currentPiece->getColor() == this->getColor()) {
        std::cout << "returned false" << std::endl;
        result = false;
      }
    }
  }
  return result;
}
