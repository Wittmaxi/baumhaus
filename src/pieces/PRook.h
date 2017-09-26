#ifndef PROOK_H
#define PROOK_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>


class PRook: public CPiece
{
    public:
        PRook(bool colorI);
        ~PRook();
        PRook(const PRook& other);
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
