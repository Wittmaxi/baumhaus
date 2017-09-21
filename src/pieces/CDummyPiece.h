#ifndef CDummyPiece_H
#define CDummyPiece_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>

//FULLY DUMMY CLASS FOR PIECES THAT ARE THERE JUST TO DO NOTHING

class CDp: public CPiece
{
    public:
        CDp(bool colorI, CPos *currentPosition);
        virtual ~CDp();
        CDp(const CDp& other);
        std::vector<int> getSquareOn();
        std::vector<std::string> getMoves();
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:

    private:
      CPos *pos;
};

#endif
