#ifndef BAUMHAUSENGINE_H
#define BAUMHAUSENGINE_H

#include "CPos.h"
#include "CPipe.h" //the pipe to XBoard
#include <string>
#include "CSquare.h"
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
        CBaumhausengine(bool debugMode);
        virtual ~CBaumhausengine();
        void startRoutine();

    protected:

    private: //members
		bool debugMode;

        int depth; //searching depth
        CPos *position; //the position: it can be loaded customly
        CPipe *pipe;
        bool color; //false = black, true = white.
        bool gotPipeInput; //if the computer has to stop thinking (is checked by a pipe)

    private: //methods
        std::string readPipe(); //reads out the pipe and returns the result. If nothing was found, it returns "NULL"
        void analyzePos(CPos _position); //analyses the position and returns a move (currently symbolysed as void). A move could be a class (CMove)
        void updateSquares();
        void setColor (bool colorI); //setter for the piece-color
        bool getColor ();

		// responses to some XBoard commands
		void pong(std::string val);
};

#endif // BAUMHAUSENGINE_H
