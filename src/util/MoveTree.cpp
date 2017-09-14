#include "MoveTree.h"

MoveTree::MoveTree() { }

MoveTree::~MoveTree() {
  deleteNode(root);
}

void MoveTree::resetTree() {
  deleteNode(root);
}

MoveTreeNode* MoveTree::insertRoot(CPos* position, bool colorToPlay) {
  if(nullptr != root) {
    // TODO throw an error or something . . .
    return;
  }

  root = new MoveTreeNode;
  root->parent = nullptr;
  root->depth = 0;
  root->hValue = 0;
  root->move = "";
  root->color = colorToPlay;
  root->position = position;

  return root;
}

MoveTreeNode* MoveTree::insertNode(MoveTreeNode* parent, std::string move) {
  if(nullptr == parent || move.empty()) {
    // TODO throw an error or something . . .
    return;
  }

  auto newNode = new MoveTreeNode;
  newNode->parent = parent;
  newNode->depth = parent->depth + 1;
  newNode->hValue = 0;
  newNode->move = move;
  newNode->color = !parent->color;
  // TODO - fix the below line so that the position is copied with the move applied.
  //newNode->position = parent->position->simulateMove(move);

  // add to parent's child list
  parent->children.push_back(newNode);

  return newNode;
}

void MoveTree::deleteNode(MoveTreeNode* node) {
  if(nullptr == node) {
    return;
  }

  // delete all children first
  for(auto child : node->children) {
    deleteNode(child);
  }

  delete node;
}