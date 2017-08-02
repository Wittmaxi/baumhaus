#ifndef CPIECE_H
#define CPIECE_H

#include "PKing.h"
#include <string>
#include <vector>
// pure virtual class. canot be instantiated.
class CPiece {
	public:
		virtual void setCoordinates (int cordXI, int cordYI){
				cordX = cordXI;
				cordY = cordYI;
		}
		bool getColor() {
			return (color);
		}
	protected:
		int cordX; //the coordinates of the piece.
		int cordY;
		bool color; //the figurine color. True means white. LOL.
};

#endif // CPIECE_H
