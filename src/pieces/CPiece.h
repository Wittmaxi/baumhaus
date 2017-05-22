#ifndef CPIECE_H
#define CPIECE_H

// pure virtual class. canot be instantiated.
class CPiece {
	public:
		virtual void calculatePossibleSquares() = 0;
		virtual void setCoordinates (int cordXI, int cordYI) = 0;
	private:
		int cordX; //the coordinates of the piece.
		int cordY;
};

#endif // CPIECE_H
