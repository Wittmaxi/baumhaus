#ifndef AssessPosition
#define AssessPosition 

#include <vector>
#include <string>
#include "../CPipe.h"

class CPos;

class AssessPositions
{ //engine that assesses the position after Jeremy silmans Criteria
 public:
  AssessPositions ();
  ~AssessPositions ();

  void setPrecision (int precisionI);
 
  void startAssessing (CPos* position, std::vector<std::string> movesI);
 		void findOpenFiles(CPos* position);
 private:
 	int precision; //how well the engine plays (0 = best, 10 = poor play)
 	std::vector<int> openFiles; // encodes what files are open. 0 = closed 1 = open for white -1 = open for black 2 = completely open

};

#endif