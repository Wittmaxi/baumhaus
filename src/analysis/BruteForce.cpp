#include "BruteForce.h"

BruteForce::BruteForce() { 
  this->maxDepth = 5;
  this->moveTree = new MoveTree();
}

BruteForce::BruteForce(int maxDepth) { 
  this->maxDepth = maxDepth;
  this->moveTree = new MoveTree();
}

BruteForce::~BruteForce() {
  delete moveTree;
}

std::string BruteForce::analyze(CPos* position, bool colorToPlay) {	
  // just being safe . . . 
  if(nullptr == moveTree) {
    moveTree = new MoveTree(); 
  }
  
  // reset tree and insert a root node.
  moveTree->resetTree();
  auto rootNode = moveTree->insertRoot(position, colorToPlay);

  // begin minimax bruteforce
  minimax(rootNode);


	return rootNode->nextMove;
}

void BruteForce::setMaxDepth(int depth) {
  this->maxDepth = (depth < 0) ? 0 : depth;
}

int BruteForce::getMaxDepth() {
  return this->maxDepth;
}

void BruteForce::minimax(MoveTreeNode* node) {
  // if we've hit the maxDepth limit (or by some chance passed it?), evaluate the node using the heuristic
  if(maxDepth <= node->depth) {
    heuristic(node);
    return;
  }

  // get a list of moves
  auto moveList = node->position->getPossibleMoves(node->color);

  // if no moves are found, evaluate the node with the heuristic
  if(0 == moveList.size()) {
    heuristic(node);
    return;
  }

  // otherwise, we continue with the minimax
  for(auto move : moveList) {
    auto childNode = moveTree->insertNode(node, move);

    // perform minimax on the child to get the best move for the opponent color
    minimax(childNode);
    
    if(node->nextMove == "" // if no next move has been determined, then take the first child
      || (childNode->color && childNode->hValue > node->hValue) // if color to play is white, maximize score
      || (!childNode->color && childNode->hValue < node->hValue)) { // if color to play is black, minimize score
      
      node->nextMove = childNode->move;
      node->hValue = childNode->hValue;
    }
  }  
}

void BruteForce::heuristic(MoveTreeNode* node) {
  
};