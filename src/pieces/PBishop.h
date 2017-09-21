#ifndef PBISHOP_H
#define PBISHOP_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>


class PBishop: public CPiece
{
    public:
        PBishop(bool colorI, CPos *currentPosition);
        PBishop(const PBishop& other);
        virtual ~PBishop();
        std::vector<int> getSquareOn();
        std::vector<std::string> getMoves();
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
