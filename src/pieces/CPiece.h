#ifndef CPIECE_H
#define CPIECE_H

// forward declaration to resolve circular dependancy
class CPos;

#include <string>
#include <vector>
#include <iostream>

class CPos;

//virtual class no instances
class CPiece {
	public:
		void setCoordinates (int cordXI, int cordYI);
		bool getColor();
		virtual std::vector<std::string> getMoves(CPos* currentPos) = 0;
    virtual CPiece* clone() = 0;
		char getPieceType();

	protected:
		int cordX; //the coordinates of the piece.
		int cordY;
		char fenType; //what fen-character the piece is.
		bool color; //the figurine color. True means white. LOL.
};

#endif // CPIECE_H
