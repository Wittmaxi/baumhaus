#ifndef PKNIGHT_H
#define PKNIGHT_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>

class PKnight: public CPiece
{
    public:
        PKnight(bool colorI);
        ~PKnight();
        PKnight(const PKnight& other);
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif
