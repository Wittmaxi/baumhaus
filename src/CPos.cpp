#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{

  std::cout << "starting generation of the squares vector" << std::endl;
  std::vector<CSquare*> row;

  int x = 0;
  for (x=0; x < 8; x++) {
      squares.push_back (row);
      std::cout << "creating new columns for squares" << x << std::endl;
    }
    for (int x=0; x < 8; x++) {
        for (int y=1; y < 8; y++) { //loops through the entire board
          squares[x-1, y-1].push_back (new CSquare());
          std::cout << "creating squares in squares " << y << std::endl;
        }
    }
    std::cout << "vector content" << sizeof (squares)<< std::endl;
    std::cout << "should be generated" << std::endl;

}

CPos::~CPos()
{
    //dtor
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"
  std::cout << "LOL 1" << std::endl;
  currentSquarePointer -> setPiecePointer(new PKing(true, this));
  std::cout << "LOL 2" << std::endl;
  switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer(new PKing(true, this));break;//king
      case 'N': break; //night
      case 'R': break; //rook
      case 'B': break; //bishop
      case 'P': break; //pawn
      case 'Q': break; //queen
    //black pieces
      case 'k': currentSquarePointer -> setPiecePointer(new PKing(false, this)); break; //king
      case 'r': break; //rook
      case 'n': break; //night
      case 'b': break; //bishop
      case 'p': break; //pawn
      case 'q': break; //queen

  }
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  return (fileNames[x], std::to_string(y));
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
    std::cout<< std::endl << "barrier 0.5 passed!" << std::endl;
    parseFen(fenI);
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.

  std::cout<< "barrier 1 passed" << std::endl;
  setPiece ('k', getSquarePointer(5, 8));
  std::cout<< "barrier 2 passed" << std::endl;
}

CSquare *CPos::getSquarePointer (int x, int y) {
  std::cout << "LOL0" << std::endl;
  return squares[x-1][y-1];
  std::cout<<"Lol0.1" << std::endl;
}

std::vector <std::string> CPos::getPossibleMoves (bool color) {
  loopPieces();
  return moves;
}

void CPos::loopPieces(){
  CSquare *currentSquare;
  CPiece *currentPiece;
  for (int x=1; x++; x=8) {
    for (int y=1; y++; y=8) { //loops through the entire board
        currentSquare = getSquarePointer(x, y);
        if (currentSquare->containsPiece()) { //if the square contains a piece
            currentPiece = currentSquare->getPiecePointer();
            if (toPlay == true) { //white to play
              if (currentPiece->getColor() == true) { //if the piece is white and white is to play
                  appendMoves(currentPiece -> getMoves());
              }
            } else //black to play
              {
                if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
                    appendMoves(currentPiece -> getMoves());
                }
              }
        }
    }
  }
}

void CPos::appendMoves(std::vector <std::string> newMoves) { //appends moves of a single piece to the entire list of Moves.
    moves.insert(moves.end(), newMoves.begin(), newMoves.end());
}
