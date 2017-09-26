#ifndef CDummyPiece_H
#define CDummyPiece_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>
#include <string>
#include <iostream>

//FULLY DUMMY CLASS FOR PIECES THAT ARE THERE JUST TO DO NOTHING

class CDp: public CPiece
{
    public:
        CDp(bool colorI);
        ~CDp();
        CDp(const CDp& other);
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:

    private:
      CPos *pos;
};

#endif
