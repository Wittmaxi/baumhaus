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
void optionError(char* long_option);
void optionError(char short_option);
void noOptionError();

bool debugMode= false;

int main (int argc, char** argv) {

	if(!evaluateArgs(argc, argv)) {
		return 0;
	}

    CBaumhausengine *engine = new CBaumhausengine(debugMode);
    
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
				if(strcmp(argv[i], "--debug") == 0) {
					debugMode = true;
				}
				else if(strcmp(argv[i], "--help") == 0) {
					showHelp();
					return false;
				}
				else {
					optionError(argv[i]);
					return false;
				}
				continue;
			}
			// otherwise, we have some short options, which may be concatenated
			int j = 1;
			if(argv[i][j] == '\0') {
				noOptionError();
				return false;
			}

			// iterate over remaining short flags
			while(argv[i][j] != '\0') {
				// if 'h' flag found just show help and terminate.
				if (argv[i][j] == 'h') {
					showHelp();
					return false;
				}

				if (argv[i][j] == 'd') {
					debugMode = true;
				}
				else {
					optionError(argv[i][j]);
					return false;
				}

				++j; // very important
			}
		}
	}

	return true;
}

void showHelp() {
	std::cout << "Usage: baumhaus [OPTIONS]" << std::endl;
	std::cout << "Baumhaus is a chess engine designed to run with xboard protocols." << std::endl << std::endl;
	std::cout << "OPTIONS" << std::endl;
	std::cout << "\t" << "-d, --debug" << "\t" << "Turn on debug console output. May interfere w/ XBoard responses." << std::endl;
	std::cout << "\t" << "-h, --help" << "\t" << "Show this helpful information." << std::endl;
	std::cout << "We are a small team maintaining the baumhaus engine. If you want to, help us on github. Contact: wittmaxi@outlook.de" << std::endl;
	// add more lines as needed. Perhaps link to git repo.
}

void optionError(char* long_option) {
	std::cout << "Error: Invalid option '" << long_option << "'" << std::endl;
}

void optionError(char short_option) {
	std::cout << "Error: Invalid option '-" << short_option << "'" << std::endl;
}

void noOptionError() {
	std::cout << "Error: no option provided" << std::endl;
}
