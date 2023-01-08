#include "treeNode.h"

TreeNode::TreeNode(std::string cntt) : content{cntt} {}

std::string TreeNode::getContent() const
{
  return this->content;

  // return "";
}

TreeNode *TreeNode::getLeftChild() const
{
  return this->leftChild;

  // return nullptr;
}
TreeNode *TreeNode::getRightChild() const
{
  return this->rightChild;

  // return nullptr;
}

void TreeNode::updateLeftChild(TreeNode *lChild)
{
  this->leftChild = lChild;
}

void TreeNode::updateChildren(TreeNode *lChild, TreeNode *rChild)
{
  // your code starts here
  this->leftChild = lChild;
  this->rightChild = rChild;
}

OperatorNode::OperatorNode(std::string cntt) : TreeNode{cntt} {}

VariableNode::VariableNode(std::string cntt) : TreeNode{cntt} {}
