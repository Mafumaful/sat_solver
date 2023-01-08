#include "tseitinTransformer.h"
#include <iostream>

TseitinTransformer::TseitinTransformer(TreeNode *root) : formulaRoot{root} {}

int TseitinTransformer::transSubformula(TreeNode *subRoot)
{
  currentNode = subRoot;
  int current_ID = this->getCurrentVarNum();
  std::string content = currentNode->getContent();
  if (content == "+")
  {
    currentNode = subRoot->getLeftChild();
    int left_ID = this->getVarNum();
    transSubformula(currentNode);
    currentNode = subRoot->getRightChild();
    int right_ID = this->getVarNum();
    transSubformula(currentNode);
    this->addOrEq(current_ID, left_ID, right_ID);
  }
  else if (content == "*")
  {
    currentNode = subRoot->getLeftChild();
    int left_ID = this->getVarNum();
    transSubformula(currentNode);
    currentNode = subRoot->getRightChild();
    int right_ID = this->getVarNum();
    transSubformula(currentNode);
    this->addAndEq(current_ID, left_ID, right_ID);
  }
  else if (content == "-")
  {
    currentNode = subRoot->getLeftChild();
    int left_ID = this->getVarNum();
    transSubformula(currentNode);
    this->addNegEq(current_ID, left_ID);
  }
  return 0;
}

void TseitinTransformer::addNegEq(int curID, int childID)
{
  std::vector<int> temp;

  // -p1v-p2
  temp.push_back(-1 * curID);
  temp.push_back(-1 * childID);
  cnf.push_back(temp);

  // p1vp2
  temp.clear();
  temp.push_back(curID);
  temp.push_back(childID);
  cnf.push_back(temp);
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID)
{
  std::vector<int> temp;

  // -p1vp2vp3
  temp.push_back(-1 * curID);
  temp.push_back(leftID);
  temp.push_back(rightID);
  cnf.push_back(temp);

  // -p2vp1
  temp.clear();
  temp.push_back(-1 * leftID);
  temp.push_back(curID);
  cnf.push_back(temp);

  // -p3vp1
  temp.clear();
  temp.push_back(-1 * rightID);
  temp.push_back(curID);
  cnf.push_back(temp);
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID)
{
  std::vector<int> temp;

  // -p1vp2
  temp.push_back(-1 * curID);
  temp.push_back(leftID);
  cnf.push_back(temp);

  // -p1vp3
  temp.clear();
  temp.push_back(-1 * curID);
  temp.push_back(rightID);
  cnf.push_back(temp);

  // p1v-p2v-p3
  temp.clear();
  temp.push_back(curID);
  temp.push_back(-1 * leftID);
  temp.push_back(-1 * rightID);
  cnf.push_back(temp);
}

std::vector<std::vector<int>> TseitinTransformer::transform()
{
  transSubformula(formulaRoot);
  std::vector<int> a;
  a.push_back(1);
  cnf.push_back(a);
  return cnf;
}

std::string TseitinTransformer::cnfString() const
{
  std::string result = "";
  return result;
}

int TseitinTransformer::getVarNum()
{
  std::string content = currentNode->getContent();        // return the current content
  if (content == "+" || content == "*" || content == "-") // if the content is an operator
  {
    return ++varIdCounter;
  }

  auto it = this->varIdTable.find(content);
  if (it == this->varIdTable.end())
  {
    varIdTable.insert(std::pair<std::string, int>(content, ++varIdCounter));
    return varIdCounter; // if the content is not include in the map
  }
  else
    return this->varIdTable.at(content);

  return 0;
}

int TseitinTransformer::getCurrentVarNum()
{
  std::string content = currentNode->getContent();        // return the current content
  if (content == "+" || content == "*" || content == "-") // if the content is an operator
  {
    return varIdCounter;
  }

  auto it = this->varIdTable.find(content);
  if (it == this->varIdTable.end())
  {
    varIdTable.insert(std::pair<std::string, int>(content, ++varIdCounter));
    return varIdCounter; // if the content is not include in the map
  }
  else
    return this->varIdTable.at(content);

  return 0;
}

int TseitinTransformer::getCount()
{
  return varIdCounter;
}