#ifndef CPOS_H
#define CPOS_H

#include "CSquare.h"
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

    protected:
        std::vector <CSquare> Squares;

    private:
};

#endif // CPOS_H
