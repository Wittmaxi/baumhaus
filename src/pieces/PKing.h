#ifndef PKING_H
#define PKING_H

#include "../CPos.h"
#include "CPiece.h"
#include "../CSquare.h"
#include <vector>
#include <string>

class PKing: public CPiece
{
    public:
        PKing(bool colorI, CPos *currentPosition);
        virtual ~PKing();
        std::vector<int> getSquareOn();
        virtual std::vector<std::string> getMoves();
        bool squareAvailable (int cordX,int cordY);
    protected:

    private:
      CPos *pos;
};

#endif // PKING_H
