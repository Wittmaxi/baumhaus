#ifndef PQUEEN_H
#define PQUEEN_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>


class PQueen: public CPiece
{
    public:
        PQueen(bool colorI, CPos *currentPosition);
        virtual ~PQueen();
        std::vector<int> getSquareOn();
        std::vector<std::string> getMoves();
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone(CPos* position);
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
