#include "AssessPosition.h"
#include "../CPos.h"

AssessPositions::AssessPositions () {

}

AssessPositions::~AssessPositions() {

}
void AssessPositions::startAssessing (CPos* position, std::vector<std::string> movesI) {
  //all these functions later will only be called on a specific precision level
	findOpenFiles(position);
}

void AssessPositions::setPrecision(int precisionI) {
	this->precision = precisionI;
}	

void AssessPositions::findOpenFiles(CPos* position) {
	for (int x = 0; x < 8; x++) { //loop trough every file
		openFiles[x] = 2; // by default every file is closed
		for (int y = 0; y < 8; y++) { //loop trough every square of this file
			if (position->getSquarePointer(x+1, y+1)->getPiecePointer()->getPieceType() == 'P') { //if the piece is a white pawn
				if (openFiles[x] < 1) {
					openFiles[x] += 1;
				} 
			} else if (position->getSquarePointer(x+1, y+1)->getPiecePointer()->getPieceType() == 'p') {
				if (openFiles[x] > -1) {
					openFiles[x] += -1;
				}
			}
		}
	}

	for (int i = 0; i < openFiles.size(); i++) {
		pipe->d(openFiles[i]);
	}
}