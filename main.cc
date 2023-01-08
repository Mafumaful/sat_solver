#include "tseitinTransformer.h"
#include "tools.h"
#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "treeNode.h"
#include "dpll.h"

int main()
{
  while (true) // continuously asking for new inputs from standard input
  {
    std::string line; // store each input line

    // your code starts here
    if (std::getline(std::cin, line)) // get input
    {
      // find space in variables
      try
      {
        bool is_valid = true;
        bool before_is_var = false;
        bool before_is_space = false;

        for (int i = 0; line[i]; i++)
        {
          if (before_is_space && ((('0' <= line[i]) && (line[i] <= '9')) || (('a' <= line[i]) && (line[i] <= 'z')) || (('A' <= line[i]) && (line[i] <= 'Z'))))
          {
            before_is_space = false;
            is_valid = false;
            break;
          }
          else if ((('0' <= line[i]) && (line[i] <= '9')) || (('a' <= line[i]) && (line[i] <= 'z')) || (('A' <= line[i]) && (line[i] <= 'Z')))
          {
            before_is_var = true;
          }
          else if (line[i] == ' ' && before_is_var)
          {
            before_is_space = true;
          }
          else
          {
            before_is_space = false;
            before_is_var = false;
          }
        }

        parseLine(line); // parse the input into the formular string and assignment string
        if (!is_valid || line.size() <= 0)
        {
          is_valid = true;
          throw "Error: invalid input";
        }

        FormulaParser *formular_parser = new FormulaParser(line); // parse the formularSt
        auto *treeroot = formular_parser->getTreeRoot();          // get the root of the parser

        TseitinTransformer *tt = new TseitinTransformer(treeroot); // Tseitin Transform
        DPLL *dpll = new DPLL(tt->transform(), tt->getCount());    // dpll
        std::cout << dpll->get_result() << std::endl;              // the result of dpll
        delete tt;
        delete dpll;
      }
      catch (const char *e)
      {
        std::cout << e << std::endl;
      }
    }
    else
      break;
  }
}