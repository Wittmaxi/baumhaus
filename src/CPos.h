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
				virtual ~CPos();
				static std::string getSquareName(int a, int b); //gets the two indexes of the board
				static std::vector <int> coordFromName (std::string squareName);
				CSquare *getSquareWithName();
				void feedFen (std::string fenI);
				CSquare *getSquarePointer(int x, int y);
				std::vector<std::string> getPossibleMoves(bool color); //color: true = white
				bool getPlayerColor();

		protected:
				std::vector<std::vector<CSquare*>> squares;
				std::vector<std::string> moves;
				std::string fen;
				bool toPlay; //which player is to play
		private:
				void parseFen(std::string fen);
				void loopPieces(); //goes through every piece to gets its moves.
				void appendMoves(std::vector <std::string> newMoves);
				void setPiece (char fenName, CSquare *currentSquarePointer);
};

#endif // CPOS_H
