#ifndef CSQUARE_H
#define CSQUARE_H

#include "pieces/CPiece.h"
#include <string>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


class CSquare
{
    public:
        CSquare(int iX, int iY);
        virtual ~CSquare();
        CPiece *getPiecePointer();
        CPiece* removePiece();
        void takePiece();
        void setPiecePointer (CPiece* input, char type);
        void addAttackers(bool color);
        void resetAttackStates();
        int returnAttackState(); //returns the protection state of a square
        int getWhiteAttackers();
        int getBlackAttackers();
        bool containsPiece();

      private:
        int calcTotalAttack(); //calculates the total amount of protection

        CPiece *contained; //stores the contained piece.
        int totalAttack;
        int whiteAttackers;
        int blackAttackers;
        int x, y; // one indexed
        bool hasPiece; //if a piece is placed on the square.
};

#endif // CSQUARE_H
