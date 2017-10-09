#ifndef PQUEEN_H
#define PQUEEN_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>

class PQueen: public CPiece
{
    public:
        PQueen(bool colorI);
        ~PQueen();
        PQueen(const PQueen& other);
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:
      std::vector <std::string> tempMoves;
    private:
      CPos *pos;
};

#endif // PQUEEN_H
