#ifndef BAUMHAUSENGINE_H
#define BAUMHAUSENGINE_H

#include "CPos.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

class CBaumhausengine
{
    public:
        CBaumhausengine();
        virtual ~CBaumhausengine();

    protected:

    private: //members
        int m_depth; //searching depth
        CPos position; //the position: it can be loaded customly
    private: //methods
        void m_analyzePos(CPos _position); //analyses the position and returns a move (currently symbolysed as void). A move could be a class (CMove)
};

#endif // BAUMHAUSENGINE_H
