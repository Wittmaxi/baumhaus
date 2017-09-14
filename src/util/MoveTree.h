#ifndef _MOVETREE_H_
#define _MOVETREE_H_

#include <vector>
#include "../CPos.h"

struct MoveTreeNode {
  MoveTreeNode* parent;
  std::vector<MoveTreeNode*> children = std::vector<MoveTreeNode*>();
  CPos* position;
  std::string move; // move made from parent
  std::string nextMove; // best move from this position for color
  bool color;
  int hValue;
  int depth;
};

class MoveTree {
public:
  MoveTree();
  ~MoveTree();
  void resetTree();
  MoveTreeNode* insertRoot(CPos* position, bool colorToPlay);
  MoveTreeNode* insertNode(MoveTreeNode* parent, std::string move);

private:
  MoveTreeNode* root;
  void deleteNode(MoveTreeNode* node);
};

#endif // _MOVETREE_H_