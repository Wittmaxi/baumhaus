#ifndef PKING_H
#define PKING_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>

class PKing : CPiece
{
    public:
        PKing();
		PKing(CPos* boardI); //gets a pointer to the used board.
        virtual ~PKing();
        std::vector<int> getSquareOn();
        void calculatePossibleSquares();


    protected:

    private:

};

#endif // PKING_H
