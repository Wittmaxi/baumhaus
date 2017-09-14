#ifndef _BRUTEFORCE_H_
#define _BRUTEFORCE_H_

#include "../CPos.h"
#include "../util/MoveTree.h"

class BruteForce {
public:
  BruteForce();
  BruteForce(int maxDepth);
  ~BruteForce();
	std::string analyze(CPos* position, bool colorToPlay); // if we want to make static, pass maxDepth here instead
  void setMaxDepth(int depth);
  int getMaxDepth();
  // TODO add handling for fixed/max depth

private:
  int maxDepth;
  MoveTree* moveTree;
  void minimax(MoveTreeNode* node); 
  void heuristic(MoveTreeNode* node);
};

#endif // !_BRUTEFORCE_H_
