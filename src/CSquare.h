#ifndef CSQUARE_H
#define CSQUARE_H

#include "PKing.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


class CSquare
{
    public:
        CSquare();
        virtual ~CSquare();

    protected:
        int protection; //how much the square is protected: example: -1 means, black has protected the square one more time as white. When a piece is on the square it doesn't count as protected
        bool hasPiece; //if a piece is placed on the square.
        CPiece *contained; //stores the contained piece.

    private:
};

#endif // CSQUARE_H
