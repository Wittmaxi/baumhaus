#ifndef PKING_H
#define PKING_H

#include "CPos"

class PKing
{
    public:
        PKing(CPos *boardI); //gets a pointer to the used board.
        virtual ~PKing();
        std::vector <int> getSquareOn();
        void calculatePossibleSquares();


    protected:

    private:
      CPos *board;

};

#endif // PKING_H
