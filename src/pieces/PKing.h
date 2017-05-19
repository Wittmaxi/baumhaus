#ifndef PKING_H
#define PKING_H

#include "../CPos.h"
#include "CPiece.h"
#include <vector>

class PKing : CPiece
{
    public:
        PKing();
		    PKing(); //gets a pointer to the used board.
        virtual ~PKing();
        std::vector<int> getSquareOn();

    protected:

    private:

};

#endif // PKING_H
