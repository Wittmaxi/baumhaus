#ifndef CPIECE_H
#define CPIECE_H

#include <string>
#include <vector>
// pure virtual class. canot be instantiated.
class CPiece {
	public:
		virtual void setCoordinates (int cordXI, int cordYI);
		bool getColor();
		std::vector<std::string> getMoves();

	protected:
		int cordX; //the coordinates of the piece.
		int cordY;
		bool color; //the figurine color. True means white. LOL.
		bool isOutOfBoard (int cordX, int cordY);
};

#endif // CPIECE_H
