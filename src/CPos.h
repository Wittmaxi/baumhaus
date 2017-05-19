#ifndef CPOS_H
#define CPOS_H

#include "CSquare.h"
#include <string>
#include <vector>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

class CPos
{
    public:
        CPos();
        virtual ~CPos();
        std::string getSquareName(int a, int b); //gets the two indexes of the board
        CSquare *getSquareWithName();
        void feedFen (std::string fenI);

    protected:
        CSquare squares[8][8];
        std::string fen;
    private:
};

#endif // CPOS_H
