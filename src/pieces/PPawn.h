#ifndef PPAWN_H
#define PPAWN_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>

class PPawn: public CPiece
{
    public:
        PPawn(bool colorI);
        ~PPawn();
        PPawn(const PPawn& other);
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordXI, int cordYI);
        bool cordsInBounds (int cordXI, int cordYI);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
