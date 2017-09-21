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
        PKing(bool colorI, CPos* currentPosition);
        virtual ~PKing();
        PKing(const PKing& other);
        std::vector<int> getSquareOn();
        virtual std::vector<std::string> getMoves();
        bool squareAvailable (int cordX, int cordY);
        CPiece* clone();
    protected:

    private:
      CPos *pos;
};

#endif // PKING_H
