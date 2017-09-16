#ifndef CPOS_H
#define CPOS_H

#include "CSquare.h"
#include "pieces/CPiece.h"
#include <string>
#include <vector>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

class CPos
{
		public:
				CPos();
				CPos(CPos* original);
				virtual ~CPos();
				static std::string getSquareName(int a, int b); //gets the two indexes of the board
				static std::vector <int> coordFromName (std::string squareName);
				CSquare *getSquareWithName();
				void feedFen (std::string fenI);
				CSquare *getSquarePointer(int x, int y);
				std::vector<std::string> getPossibleMoves(bool color); //color: true = white
				bool getPlayerColor();
				bool movePointers (std::string move);
				void writeBitBoard(); //function that simply prints a board of bools with the values of containsPiece()
				void setColor(bool colorI);
				std::string getFen ();

		private:
				std::vector<std::vector<CSquare*>> squares;
				std::vector<std::string> moves;
				std::string fen;
				bool toPlay; //which player is to play
		private:
				std::vector <std::string> getOutOfCheck(std::vector <std::string> movesI, bool colorI);
			  bool kingIsInCheck (bool color);
				std::pair<int, int> getKingCoords(bool color);
				void parseFen(std::string fen);
				std::vector <std::string> loopPieces(bool colorI); //goes through every piece to gets its moves.
				void setPiece (char fenName, CSquare *currentSquarePointer);
				void updateFen (); //updates the current fen after a move
};

#endif // CPOS_H
