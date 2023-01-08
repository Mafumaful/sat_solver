#include "parser.h"
#include "treeNode.h"
#include "tokenizer.h"

FormulaParser::FormulaParser(std::string ln) : tknzr{new Tokenizer{ln}} {}

TreeNode *FormulaParser::parseConjTerm()
{
  // parse non-terminal ConjTerm in the grammar
  auto left = parseTerm();
  if (tknzr->getToken().type == "VAR" || tknzr->getToken().type == "CONSTANT" || tknzr->getToken().type == "NOT")
  {
    throw "Error: invalid input";
  }

  while (tknzr->getToken().type == "AND") // parse term detecting "AND" world
  {
    auto *Operator = new OperatorNode(tknzr->getToken().content);
    tknzr->advanceToken();
    Operator->updateChildren(left, parseConjTerm());
    return Operator;
  }
  return left;
}

TreeNode *FormulaParser::parseTerm()
{
  Token token = tknzr->getToken();

  if (!tknzr->hasToken() || token.type == "ERR")
  {
    throw "Error: invalid input";
  }

  if (token.type == "LEFTPARENT")
  {
    this->lparent_c++;
    tknzr->advanceToken();
    auto *Varia = parseFormula();
    if (tknzr->getToken().type != "RIGHTPARENT")
    {
      throw "Error: invalid input";
    }
    this->lparent_c--;
    tknzr->advanceToken();
    return Varia;
  }
  else if (token.type == "VAR")
  {
    auto *Varia = new VariableNode(token.content);
    tknzr->advanceToken();
    return Varia;
  }
  else if (token.type == "NOT")
  {
    auto *Operator = new OperatorNode(token.content);
    tknzr->advanceToken();
    Operator->updateLeftChild(parseTerm());
    return Operator;
  }
  else
  {
    throw "Error: invalid input";
  }
}

TreeNode *FormulaParser::parseFormula()
{
  // parse non-terminal Formula in the grammar

  auto left = parseConjTerm();
  if (tknzr->getToken().type == "VAR" || tknzr->getToken().type == "CONSTANT" || tknzr->getToken().type == "NOT")
  {
    throw "Error: invalid input";
  }
  while (tknzr->getToken().type == "OR")
  {
    auto *Operator = new OperatorNode(tknzr->getToken().content);
    tknzr->advanceToken();
    Operator->updateChildren(left, parseFormula());
    return Operator;
  }

  if (this->lparent_c < 1 && tknzr->getToken().type == "RIGHTPARENT")
  {
    throw "Error: invalid input";
  }

  return left;
}

TreeNode *FormulaParser::getTreeRoot()
{

  // parse the Boolean formula and return the root node of the formula syntax tree
  std::vector<std::string> unwanted_str = {"ERR", "ASSIGNMENT", "COMMA"};
  if (!tknzr->member_is_valid(unwanted_str)) // check if every thing is right
  {
    throw "Error: invalid input";
  }
  return this->parseFormula(); // return the root of the Formular

  // return nullptr;
}

FormulaParser::~FormulaParser()
{

  delete tknzr;
}

AssignmentParser::AssignmentParser(std::string ln) : tknzr{new Tokenizer{ln}} {}

std::map<std::string, bool> AssignmentParser::parseAssignment()
{
  std::map<std::string, bool> results;

  // this function is to parse assiment and turn it into map that we can find correspond variable value
  while (tknzr->hasToken())
  {
    std::string var;
    std::string constant;

    if (tknzr->getToken().type == "EOF") // if there is no token or if it's end
      return results;

    if (tknzr->getToken().type == "VAR")
    {
      var = tknzr->getToken().content;
      tknzr->advanceToken();
    }
    else // the first token should be the variable
    {
      throw "Error: invalid input";
    }

    if (tknzr->getToken().type == "EOF")
    {
      return results;
    }
    else
    {
      throw "Error: invalid input";
    }
  }
  return results;
}

AssignmentParser::~AssignmentParser()
{
  delete tknzr;
}
