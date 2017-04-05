#ifndef BAUMHAUSENGINE_H
#define BAUMHAUSENGINE_H

#include "CPos.h"
<<<<<<< HEAD
#include "CPipe.h" //the pipe to XBoard
#include <string>
=======
#include "CSquare.h"
>>>>>>> master
#include <vector>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

//the main class that avaluates everything

class CBaumhausengine
{
    public:
        CBaumhausengine();
        virtual ~CBaumhausengine();

    protected:

    private: //members
        int m_depth; //searching depth
        CPos *position; //the position: it can be loaded customly
        CPipe *pipe;
    private: //methods
        std::string readPipe(); //reads out the pipe and returns the result. If nothing was found, it returns "NULL"
        void m_analyzePos(CPos _position); //analyses the position and returns a move (currently symbolysed as void). A move could be a class (CMove)
};

#endif // BAUMHAUSENGINE_H
