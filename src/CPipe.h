#ifndef CPIPE_H
#define CPIPE_H

#include <string>
#include <vector>
#include <pthread.h>
#include <mutex>

#define basPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -"
/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/


// connects to xboard and evaluates the inputs

extern const std::string NEWLINE_CMD;

class CPipe
{
    public:
        CPipe(bool debugMode);
        virtual ~CPipe();
        std::string dequeueInputMessage(bool waitForMessage);
		void queueOutputMessage(std::string message);

		// debugging output
		void d(const char* message);
		void d(const std::string message);

		// IO loops
		void startInput();
		void startOutput();

    protected:
		void queueInputMessage(std::string message);
		std::string dequeueOutputMessage(bool waitForMessage);
		/*
		XBoard Commands
		*/
		// first command from XBoard. informas engine xboard is in use
		void xboard();
		// w/ version >= 2, xboard provides protocol version. we support version 2
		void protover(std::string version);
		// xboards's response to the engine's feature request
		void featureResponse(bool accepted, std::string featureName);
		// prepare a new game, enter force mode
		void newGame();
		// prepare this variant of chess
		void variant(std::string variant);
		// toggle random mode
		void random();
		// enter force mode
		void force();
		// exit force mode and play current color
		void go();
		//// similar to go(). exit force mode, play opposite color. enter pondering, and start opponent's clock.
		//void playOther();
		// [LEGACY] opponent is white, engine is black, stop clocks
		void white();
		// [LEGACY] opponent is black, engine is white, stop clocks
		void black();
		// ???
		void setLevel(int movesPerTimeConrol, std::string base, int increment);
		// set time controls for game
		//void setTimeControl(std::string control);
		//// set depth search limit
		//void setDepth(int depth);
		//// set nodes per second. if this is set the engine abandons the wall clock, an searches based on number of nodes. e.g. an NPS of 500 would mean iterating over 500
		//void setNodesPerSecond(int nodes);
		// set time for the engine
		void setTime(int centiseconds);
		// set time for opponent
		void setOpponentTime(int centiseconds);
		// move by the user. move expressed in coordinate algebraic notation.
		void userMove(std::string move);
		// engine must submit a move immediately
		void moveNow();
		// ping from xboard. reply with pong() after processing all previous commands.
		void ping(std::string val);
		//// opponent has offered a draw.
		//void draw();
		//// result of the game from xboard. normally sent after a game has ended.
		//void result(std::string result, std::string comment);
		//// set the board using FEN notation
		//void setboard(std::string fenRep);
		//// [LEGACY] edit mode. The engine can setup positions based on various subsequent input.
		//void editMode();
		//// user has asked for a hint.
		//void hint();
		//// undo the previous move. xboard will handle putting the engine in force mode prior to this command.
		//void undo();
		//// user retracts previous move. undo two moves, one for each player. continue playing same color
		//void remove();
		// toggle pondering.
		void togglePondering(bool ponder);
		// toggle pondering output.
		void togglePonderingOutput(bool showOutput);
		//// enter analyze mode
		//void analyze();
		// the xboard sends the opponent's name
		void opponentName(std::string name);
		//// sends ratings for both sides. the engine's rating is first
		//void rating(std::string engineRating, std::string opponentRating);
		//// ics hostname for playing on chess servers
		//void ics(string hostname);
		//// the opponent is a computer. possibly modify behavior?
		//void computer();
		// pause the game
		void pause();
		// resume the game
		void resume();


    private:
		bool isRunning;
		// debug flag
		bool debugMode;
		// queue for commands to the engine. 
		// some commands may be handled by the Pipe Directly, e.g. replying to the 'xboard' command, however others require input from the engine, e.g. '?'.
		// for a queue of size n, index 0 is the back of the queue, and index n-1 is the front. (simpler processing)
		std::vector<std::string> inputMessageQueue;
		std::vector<std::string> outputMessageQueue;
		// threads for IO operations
		pthread_t inThread;
		pthread_t outThread;
		// beginning for input thread
		static void* startInputThread(void* instance);
		// beginning for output thread
		static void* startOutputThread(void * instance);
		// mutex's to make sure we don't have any funny threading issues
		std::mutex inputMutex;
		std::mutex outputMutex;
};

#endif // CPIPE_H
