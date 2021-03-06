#ifndef PROOK_H
#define PROOK_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>


class PRook: public CPiece
{
    public:
        PRook(bool colorI, CPos *currentPosition);
        virtual ~PRook();
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
