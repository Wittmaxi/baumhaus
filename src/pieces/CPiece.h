#ifndef CPIECE_H
#define CPIECE_H

#include <string>
#include <vector>
#include <iostream>

//virtual class no instances

class CPiece {
	public:
		virtual void setCoordinates (int cordXI, int cordYI);
		bool getColor();
		virtual std::vector<std::string> getMoves() =0;
		char getPieceType();
		virtual CPiece* Clone(CPos* position) = 0; 

	protected:
		int cordX; //the coordinates of the piece.
		int cordY;
		char fenType; //what fen-character the piece is.
		bool color; //the figurine color. True means white. LOL.
};

#endif // CPIECE_H
