#ifndef PPAWN_H
#define PPAWN_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>

class PPawn: public CPiece
{
    public:
        PPawn(bool colorI, CPos* currentPosition);
        virtual ~PPawn();
        std::vector<int> getSquareOn();
        virtual std::vector<std::string> getMoves();
        bool squareAvailable (int cordXI, int cordYI);
        bool cordsInBounds (int cordXI, int cordYI);
        CPiece* clone(CPos* position);
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
