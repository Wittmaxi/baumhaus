#ifndef PKNIGHT_H
#define PKNIGHT_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>

class PKnight: public CPiece
{
    public:
        PKnight(bool colorI, CPos* currentPosition);
        ~PKnight();
        PKnight(const PKnight& other);
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
