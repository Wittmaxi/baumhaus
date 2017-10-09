#ifndef CSQUARE_H
#define CSQUARE_H

#include "pieces/CPiece.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


class CPos;

class CSquare
{
    public:
        CSquare(int iX, int iY);
        virtual ~CSquare();
        CSquare(const CSquare& other);
        CPiece *getPiecePointer();
        CPiece* removePiece();
        void takePiece();
        void setPiecePointer (CPiece* input);
        bool containsPiece();

      private:
        int calcTotalAttack(); //calculates the total amount of protection
        int protection;
        CPiece *contained; //stores the contained piece.
        int x, y; // one indexed
        bool hasPiece; //if a piece is placed on the square.
};

#endif // CSQUARE_H
