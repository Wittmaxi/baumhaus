#include "CPos.h"
#include <vector>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

CPos::CPos()
{
    //ctor
}

CPos::~CPos()
{
    //dtor
}

std::string CPos::getSquareName(int x, int y) {

}

void CPos::feedFen (std::string fenI) {
    fen = fenI;
}

void CPos::parseFen (std::string fen) {
  //TODO parse the FEN to feed it into each square.
  while (true) { //nothingly nothingness.
    std::vector<std::string> rows = split(fen.c_str(), '/');
    for (unsigned int rowNum = 0; rowNum < 8; rowNum++) {
      std::string row = rows[rowNum];
      int place = 0;
      char ch = row[place];
      if (!isNumeric(ch)){ // means unoccupied place
        CSquare cSquare;
        cSquare.setPiece(ch);
        squares[rowNum][place] = cSquare;
        place++;
      } else {
        place += ch;
      }

      //row++;
    }
  }
}

CSquare *CPos::getSquarePointer (int x, int y) {
  return &squares[x][y];
}

std::vector <std::vector <std::string>> getPossibleMoves (bool color) {

}

std::vector<std::string> CPos::split(const char *str, char c = ' '){
  std::vector<std::string> result;
  do{
     const char *begin = str;
     while(*str != c && *str)
         str++;

     result.push_back(std::string(begin, str));

 } while (0 != *str++);

 return result;
}

/* Checks whether given character is a Numeric value of not */
bool CPos::isNumeric(const char c){
  return (c > 47 && c < 58);
}
