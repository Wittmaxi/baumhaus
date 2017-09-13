#include "CPos.h"
#include <iostream>
#include "pieces/CPiece.h"
#include "pieces/PKing.h"
#include "pieces/CDummyPiece.h"
#include "pieces/PBishop.h"
#include "pieces/PRook.h"
#include "pieces/PKnight.h"
#include "pieces/PPawn.h"
#include "pieces/PQueen.h"
#include "CPipe.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{

  std::vector<CSquare*> row;
  int x = 1;
  for (x=1; x <= 8; x++) {
      squares.push_back (row);
    }
    for (int y=1; y <= 8; y++) {
        for (int x=1; x <= 8; x++) { //loops through the entire board
          squares[y-1]. push_back (new CSquare(x, y));
        }
    }

}

CPos::~CPos()
{
    //dtor
    int x = 1;
      for (int y=1; y <= 8; y++) {
          for (int x=1; x <= 8; x++) { //loops through the entire board
            CSquare* currentSquare = squares [x-1][y-1];
            delete currentSquare;
          }
      }
}

void CPos::setPiece (char fenName, CSquare *currentSquarePointer) { //ONLY!!! at startup or to reset the position/setting a FEN. If there is no piece, fenName = "V"

  switch (fenName) {
    //white pieces
      case 'K': currentSquarePointer -> setPiecePointer (new PKing(true, this)); break;//king
      case 'N': currentSquarePointer -> setPiecePointer (new PKnight(true, this)); break; //knight
      case 'R': currentSquarePointer -> setPiecePointer (new PRook(true, this)); break; //rook
      case 'B': currentSquarePointer -> setPiecePointer (new PBishop(true, this)); break; //bishop
      case 'P': currentSquarePointer -> setPiecePointer (new PPawn(true, this));break; //pawn
      case 'Q': currentSquarePointer -> setPiecePointer (new PQueen(true, this)); break; //queen
      case 'D': currentSquarePointer -> setPiecePointer (new CDp(true, this)); break;
    //black pieces
      case 'k': currentSquarePointer -> setPiecePointer (new PKing(false, this)); break; //king
      case 'r': currentSquarePointer -> setPiecePointer (new PRook(false, this));break; //rook
      case 'n': currentSquarePointer -> setPiecePointer (new PKnight(false, this)); break; //knight
      case 'b': currentSquarePointer -> setPiecePointer (new PBishop(false, this)); break; //bishop
      case 'p': currentSquarePointer -> setPiecePointer (new PPawn(false, this));break; //pawn
      case 'q': currentSquarePointer -> setPiecePointer (new PQueen(false, this)); break; //queen

      case 'd': currentSquarePointer -> setPiecePointer (new CDp(false, this)); break;
  }
}

std::string CPos::getSquareName(int x, int y) { //gets the algebraic notation name of the square
  const std::vector <char> fileNames  = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  std::string currentName;
  currentName = fileNames[x-1] + std::to_string(y);
  return (currentName);
}

std::vector <int> CPos::coordFromName (std::string squareName) {
  if (squareName.size() > 2) {
    pipe->d("Error in square Name conversion");
  } else {
    //ok, this is messy, but: we take the character value of the squares character and remove what is before A
    std::vector <int> returnVector;
    returnVector.push_back (squareName [0] -96);
    returnVector.push_back (squareName [1] -48);
    return returnVector;
  }
}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
    parseFen(fenI);
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.
  setPiece ('k', getSquarePointer(5, 8)); //hardcoding some pieces in for the time-being
  setPiece ('b', getSquarePointer(6, 8));
  setPiece ('b', getSquarePointer(3, 8));
  setPiece ('r', getSquarePointer(8, 8));
  setPiece ('r', getSquarePointer(1, 8));
  setPiece ('n', getSquarePointer(2, 8));
  setPiece ('n', getSquarePointer(7, 8));
  setPiece ('q', getSquarePointer(4, 8));
  setPiece ('p', getSquarePointer(1, 7));
  setPiece ('p', getSquarePointer(2, 7));
  setPiece ('p', getSquarePointer(3, 7));
  setPiece ('p', getSquarePointer(4, 7));
  setPiece ('p', getSquarePointer(5, 7));
  setPiece ('p', getSquarePointer(6, 7));
  setPiece ('p', getSquarePointer(7, 7));
  setPiece ('p', getSquarePointer(8, 7));
  setPiece ('K', getSquarePointer(5, 1)); //WHITE PIECES
  setPiece ('B', getSquarePointer(6, 1));
  setPiece ('B', getSquarePointer(3, 1));
  setPiece ('R', getSquarePointer(8, 1));
  setPiece ('R', getSquarePointer(1, 1));
  setPiece ('N', getSquarePointer(2, 1));
  setPiece ('N', getSquarePointer(7, 1));
  setPiece ('Q', getSquarePointer(4, 1));
  setPiece ('P', getSquarePointer(1, 2));
  setPiece ('P', getSquarePointer(2, 2));
  setPiece ('P', getSquarePointer(3, 2));
  setPiece ('P', getSquarePointer(4, 2));
  setPiece ('P', getSquarePointer(5, 2));
  setPiece ('P', getSquarePointer(6, 2));
  setPiece ('P', getSquarePointer(7, 2));
  setPiece ('P', getSquarePointer(8, 2));
}

CSquare* CPos::getSquarePointer (int x, int y) {
  return squares[y-1][x-1];
}

std::vector <std::string> CPos::getPossibleMoves (bool colorI) {
  moves.clear();
  moves = loopPieces(colorI);
  for (int i = 0; i < moves.size(); i++) {
    pipe -> d(moves[i]);
  }
  pipe -> d("setting attack states");
  setSquaresAttackStates();
  pipe -> d("ATTACK STATES SET");
  writeAttackStates();

  /*pipe -> d("Checking if King in check. Color :", false);
  pipe -> d(colorI ? "1" : "0");
  moves = getOufOfCheck(moves, colorI); //removes every move that brings the king into check
  if (moves.size() == 0) {
    //checkmate
    pipe -> d ("");
  }
  */
  std::vector<std::string> tmp;
  for (int i = 0; i < moves.size(); i++) { //remove moves that are only meant for the Attack-setters
    if (moves[i].substr (4, 2) != "AS") {
      tmp.push_back (moves[i]);
    }
  }
  moves = tmp;

  return moves;
}

std::vector<std::string> CPos::loopPieces(bool colorI){
  CSquare *currentSquare;
  CPiece *currentPiece;
  std::vector<std::string> tempMoves;
  for (int x=1; x<= 8; x++) {
		for (int y=1; y <= 8; y++) { //loops through the entire board
			currentSquare = getSquarePointer(x, y);
			if (currentSquare->containsPiece()) { //if the square contains a piece
				currentPiece = currentSquare->getPiecePointer();
				if (colorI == true) { //white to play
					if (currentPiece->getColor() == true) { //if the piece is white and white is to play
            tempMoves = appendMoves(currentPiece -> getMoves(), tempMoves);
					}
				}
				else { //black to play
					if (currentPiece -> getColor() == false) { //if the piece is black and black is to play
            tempMoves = appendMoves(currentPiece -> getMoves(), tempMoves);
					}
				}
			}
		}
	}
  return tempMoves;
}

std::vector<std::string> CPos::appendMoves(std::vector <std::string> newMoves, std::vector<std::string> oldMoves) { //appends moves of a single piece to the entire list of Moves.
if (newMoves.size() > 0) {
    oldMoves.insert(oldMoves.end(), newMoves.begin(), newMoves.end());
  }
  return oldMoves;
}

bool CPos::getPlayerColor () {
  return toPlay;
}

void CPos::setSquaresAttackStates () {
  CSquare* currentSquare;
  std::vector <std::string> movesWhite = loopPieces (true);
  std::vector <std::string> movesBlack = loopPieces (false);
  int x, y;
  std::vector <int> temp;
    for (int i = 0; i < movesWhite.size(); i++) {
      pipe -> d(movesWhite[i]);
    }
    for (int i = 0; i < movesBlack.size(); i++) {
      pipe -> d(movesBlack[i]);
    }
  std::string currentMove;
  for (int i = 0; i < movesWhite.size(); i++){
    currentMove = movesWhite[i];
    if (currentMove.substr(4, 2) != "MO") {//resolve the flag of the move like "MO" (Other flags, if needed)
      pipe-> d (currentMove.substr(2,2));

      temp = coordFromName(currentMove.substr (2, 2));
      x = temp[0];
      y = temp[1];
      currentSquare = getSquarePointer(x, y);

      currentSquare->addAttackers (true);
    }
    pipe -> d("ATTACKSTATES. Convolution: ", false, false);
    pipe -> d(i);
  }
  for (int i = 0; i < movesBlack.size(); i++){
    currentMove = movesBlack [i];
    if (currentMove.substr(4, 2) != "MO") {//resolve the flag of the move like "MO" (Other flags, if needed)
      temp = coordFromName(currentMove.substr (2, 2));
      x = temp[0];
      y = temp[1];
      currentSquare = getSquarePointer(x, y);

      currentSquare->addAttackers (false);
    }
    pipe -> d("ATTACKSTATES (black). Convolution: ", false, false);
    pipe -> d(i);
  }
}

bool CPos::kingIsInCheck(bool colorI) { //returns, wether the king that is to play is in check
  std::pair <int, int> tmp;
  tmp = getKingCoords(colorI);
  pipe -> d ("GOT KING COORDS");
  CSquare* currentSquare =  getSquarePointer (std::get<0> (tmp), std::get<1> (tmp));
  pipe ->d ("got current Square");
  if (colorI) { //white king
    if (currentSquare->getWhiteAttackers() != 0) {
      return true;
    }
  } else {
    if (currentSquare->getBlackAttackers() != 0) {
        return true;
    }
  }
  return false;
}

std::pair<int, int> CPos::getKingCoords(bool colorI) {
  CSquare* currentSquare;
  CPiece* currentPiece;

  pipe -> d("finding the kings coordinates");
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      currentSquare = getSquarePointer(x+1, y+1);
      if (currentSquare->containsPiece()) {
        currentPiece = currentSquare-> getPiecePointer ();
        if ((currentPiece->getPieceType() == 'K' && colorI == true) || (currentPiece->getPieceType() == 'k' && colorI == false)) {
          std::pair<int, int> tmp = std::make_pair (x, y);
          pipe -> d(std::get<0> (tmp), false);
          pipe -> d(std::get<0> (tmp));
          return tmp;
        }
      }
    }
  }
  std::pair<int, int> tmp = std::make_pair (-1, -1); //edge-case
  return tmp;
}

std::vector <std::string> CPos::getOufOfCheck(std::vector <std::string> movesI, bool colorI) {
  pipe -> d("Remove non-King moves");
  std::pair <int, int> temp = getKingCoords(colorI);
  std::vector <std::string> newMoves;
  pipe -> d("Read out the Kings-coordinates");
  std::string kingLocation = getSquareName (std::get<0> (temp), std::get<1> (temp));
  pipe -> d("Looping though every move");
  this -> writeBitBoard ();
  this -> writeAttackStates();
  CPos *newPos; //variable to test the current position on

  for (int i = 0; i < movesI.size(); i++) {
    newPos = new CPos(*this);
    pipe -> d ("moving pointers");
    newPos->movePointers (movesI [i]);
    newPos->writeBitBoard();
    newPos->writeAttackStates();
    pipe -> d ("Is the king in check after the last move?");
    if (!(newPos->kingIsInCheck(colorI))) {
      newMoves.push_back (movesI [i]);
    }
    pipe -> d(i);
    delete &newPos;
  }
  return newMoves;
}

bool CPos::movePointers (std::string move) {
  std::vector<int> moveStartField = coordFromName (move.substr (0, 2));
  std::vector<int> moveEndField = coordFromName (move.substr (2, 2));

  CSquare* startSquare = this-> getSquarePointer (moveStartField [0], moveStartField[1]);;
  CSquare* endSquare = this-> getSquarePointer (moveEndField[0], moveEndField[1]);

  if (startSquare->containsPiece() == false)  {return false;} // if there is no piece in the start square, return an error

  if (startSquare->getPiecePointer()->getColor() == this-> toPlay) {
      if (endSquare -> containsPiece()){ //if the piece is taking another piece or even passing on a piece of its own color
          if (endSquare->getPiecePointer()->getColor() == this-> toPlay) { //checks if the piece is of the same color
              return false;
          } else {
              pipe-> d("Taking a piece");
              endSquare->takePiece();
              endSquare->setPiecePointer(startSquare->removePiece());
          }
      } else {
          pipe-> d("movind a piece");
          endSquare->setPiecePointer (startSquare->removePiece());
      }
    } else {
      return false;
    }
}

void CPos::writeBitBoard() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      pipe -> d(getSquarePointer(x+1, y+1)->containsPiece(), false, false);
    }
    pipe->d("");
  }
}

void CPos::writeAttackStates() {
  pipe->d("", false, true);
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      pipe -> d(getSquarePointer(x+1, y+1)->returnAttackState(), false, false);
      pipe -> d(" ", false, false);
    }
    pipe->d("");
    pipe->d("", false, true);
  }
  pipe->d ("");
}

void CPos::setColor(bool colorI) {
  toPlay = colorI;
}
