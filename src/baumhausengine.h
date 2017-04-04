#ifndef BAUMHAUSENGINE_H
#define BAUMHAUSENGINE_H

#include "CPos.h"

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

class baumhausengine
{
    public:
        baumhausengine();
        virtual ~baumhausengine();

    protected:

    private: //members
        int m_depth; //searching depth
    private: //methods
        m_analyzePos(CPos _position);
};

#endif // BAUMHAUSENGINE_H
