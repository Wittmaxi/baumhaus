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
        ~PPawn();
        PPawn(const PPawn& other);
        std::vector<int> getSquareOn();
        std::vector<std::string> getMoves();
        bool squareAvailable (int cordXI, int cordYI);
        bool cordsInBounds (int cordXI, int cordYI);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
