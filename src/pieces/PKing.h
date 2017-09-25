#ifndef PKING_H
#define PKING_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>
#include <iostream>

class PKing: public CPiece
{
    public:
        PKing(bool colorI);
        ~PKing();
        PKing(const PKing& other);
        std::vector<int> getSquareOn();
        std::vector<std::string> getMoves(CPos* currentPos);
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:

    private:
      CPos *pos;
};

#endif // PKING_H
