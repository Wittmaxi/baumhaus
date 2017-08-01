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

		// engine's time in centiseconds
		int mTime;
		// opponent's time in centiseconds
		int oTime;
		// random flag. true = use random
		bool random;
		// tracks which player is on turn. false = balck, true = white
		bool colorOnTurn;


    private: //methods
		// initialize the engine for a new game
		void init();

        void analyzePos(); //analyses the position and returns a move (currently symbolysed as void). A move could be a class (CMove)
		void ponderPos(); // ponders. this occurs if/when it's the opponent's turn
        void updateSquares();
        void setColor (bool colorI); //setter for the piece-color
        bool getColor ();

		/* responses to some XBoard commands */
		// pong the UI
		void pong(std::string val);
		// make move and update internal board. Both user moves and engines moves should pass thorugh here.
		void makeMove(std::string move);
};

#endif // BAUMHAUSENGINE_H
