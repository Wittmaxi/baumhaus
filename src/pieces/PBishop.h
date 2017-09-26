#ifndef PBISHOP_H
#define PBISHOP_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>


class PBishop: public CPiece
{
    public:
        PBishop(bool colorI);
        PBishop(const PBishop& other);
        ~PBishop();
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
