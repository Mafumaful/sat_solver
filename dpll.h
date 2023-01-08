#ifndef DPLL_H
#define DPLL_H

#include <vector>
#include <string>
#include <iostream>

enum status
{
    sat,    // satisfied
    unsat,  // unsatisfied
    move_on // continue to move
};

class Formular
{
public:
    std::vector<std::vector<int>> clauses; // store the clauses
    int n_literal = 0;
    Formular(std::vector<std::vector<int>> cls, int nlit);
    Formular(const Formular &f);
};

class DPLL
{
private:
    Formular fml;

public:
    DPLL(std::vector<std::vector<int>> cls, int nlit);
    int recursive_dpll(Formular f, int asmt); // do the recursive_dpll

    // judge
    int judge_is_satisfied(Formular f) const;

    // bcp
    int bcp(Formular &f, int asmt); // it's a reference

    // assignment
    int choose_value(Formular f) const;

    // result
    std::string get_result();
};

#endif
