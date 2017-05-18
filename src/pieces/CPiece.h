#ifndef CPIECE_H
#define CPIECE_H

// pure virtual class. canot be instantiated.
class CPiece {
public:
	virtual void calculatePossibleSquares() = 0;
};

#endif // CPIECE_H