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
        CBaumhausengine();
        virtual ~CBaumhausengine();
        void startRoutine();

    protected:

    private: //members

        pthread_t routineThread;

        int depth; //searching depth
        CPos *position; //the position: it can be loaded customly
        bool color; //false = black, true = white.
        bool gotPipeInput; //if the computer has to stop thinking (is checked by a pipe)
        std::vector<std::string> movesList;

		// engine's time in centiseconds
		int mTime;
		// opponent's time in centiseconds
		int oTime;
		// random flag. true = use random
		bool random;
		// tracks which player is on turn. false = black, true = white
		bool colorOnTurn;

    bool firstTime; //DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG

    private: //methods
		    // initialize the engine for a new game
		    void init();

        void analyzePos(); //analyses the position and returns a move (currently symbolysed as void). A move could be a class (CMove)
		    void ponderPos(); // ponders. this occurs if/when it's the opponent's turn
        void updateSquares();
        void setColor (bool colorI); //setter for the piece-color
        bool getColor ();
        bool movePointers (std::string move); //moves the piece pointers. Returns false on error

		/* responses to some XBoard commands */
		// pong the UI
		void pong(std::string val);
		// make move and update internal board. Both user moves and engines moves should pass thorugh here.
		void makeMove(std::string move);
    // go command routine
    void go();
    // plyOther command routine
    void playOther();
    // function to validate user's move input
    bool validateMove(std::string move);


        /// needed to assess the position

        //void assessPosition(cPos *position);

        /// run by assessPosision(). All these functions also create candidate moves that will be evaluated by a NN and then calculated through.

        //void findMaterialDiff(CPos *position)
        //void findOpenLines(cPos *position);
        //void findHoles(cPos *posision);
        //void findBadPieces(cPos *position);
        //void findUnsafeKing(cPos *position);
        //void findAttackingOpportunity(cPos *position);
        //void findWeakPawns(cPos *position);
        //void findHangingPieces(cPos *position);
        //void findStrongPoints(cPos *position);
};

#endif // BAUMHAUSENGINE_H
