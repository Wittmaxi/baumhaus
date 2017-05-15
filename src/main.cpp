#include "baumhausengine.h" //the actual engine
#include "CPipe.h" //the pipe between the engine and the UI
#include <iostream>
#include <cstring>

/*

Baumhaus Engine 2017

By publishing this engine, you agree to publish the code with it.

This code comes with no warranty at all; not even the warranty to work properly and comercially

*/

bool evaluateArgs(int argc, char** argv);
void showHelp();
void optionError(char* option);

using namespace std;

int main (int argc, char** argv) {

	if(!evaluateArgs(argc, argv)) {
		return 0;
	}

    CBaumhausengine *engine = new CBaumhausengine();
	CPipe *pipe = new CPipe();
    cout << "Baumhaus Engine started up... Waiting for Signals" << endl;
	
	// wait for commands
	pipe->run();

    engine -> startRoutine();
}

bool evaluateArgs(int argc, char** argv) {
	if(argc <= 1) {
		return true;
	}

	// evaluate each argument
	for(int i = 1; i < argc; ++i) {
		if(strlen(argv[i]) <= 1) {
			return false;
		}
		if(argv[i][0] == '-') { // option detected
			if(argv[i][1] == '-') { // long option, simple match
				if(argv[i] == "--debug") {
					// TODO: globally apply this option
				}
				else if(argv[i] == "--help") {
					showHelp();
					return false;
				}
				else {
					optionError(argv[i]);
					false;
				}
				continue;
			}
			// otherwise, we have some short options, which may be concatenated
			if (strchr(argv[i], 'h')) {
				showHelp();
				return false;
			}
			else if (strchr(argv[i], 'd')) {
				// TODO: globally apply this option
			}
			else {
				optionError(argv[i]);
			}
		}
	}
}

void showHelp() {
	cout << "Usage: baumhaus [OPTIONS]" << endl;
	cout << "Baumhaus is a chess engine designed to run with xboard protocols." << endl << endl;
	cout << "OPTIONS" << endl;
	cout << "\t" << "-d, --debug" << "\t" << "Turn on debug console output. May interfere w/ XBoard responses." << endl;
	cout << "\t" << "-h, --help" << "\t" << "Show this helpful information." << endl;
	// add more lines as needed. Perhaps link to git repo.
}

void optionError(char* option) {
	cout << "Error: Invalid option '" << (option[0] != '-' ? '-' : '\0') << option << "'" << endl;
}