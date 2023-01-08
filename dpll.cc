#include "dpll.h"

/**
 * @brief Construct a new Formular:: Formular object
 * construct a formular from scratch
 *
 * @param cls clauses
 * @param nlit the number of literal
 */
Formular::Formular(std::vector<std::vector<int>> cls, int nlit) : clauses(cls), n_literal(nlit) {}

/**
 * @brief Construct a new Formular:: Formular object
 * copy of a new formular
 *
 * @param f formular
 */
Formular::Formular(const Formular &f) // copy the formular
{
    this->clauses = f.clauses;
    this->n_literal = f.n_literal;
}

// DPLL algorithm
DPLL::DPLL(std::vector<std::vector<int>> cls, int nlit) : fml(cls, nlit) {}

/**
 * @brief get the result of the formular
 *
 * @return std::string the judgement whether the formular is sat or unsat
 */
std::string DPLL::get_result()
{
    if (this->recursive_dpll(this->fml, 0) == status::sat)
    {
        return "sat";
    }
    else
        return "unsat";
}

/**
 * @brief BCP transformation
 *
 * @param f input formular, use reference
 * @return int the result of BCP
 */
int DPLL::bcp(Formular &f, int asmt)
{
    if (asmt == 0)
    {
        return this->judge_is_satisfied(f);
    }

    for (long unsigned int i = 0; i < f.clauses.size();)
    {
        bool add = true;
        for (long unsigned int j = 0; j < f.clauses[i].size(); j++)
        {
            if (f.clauses[i][j] == asmt) // if find
            {
                f.clauses.erase(f.clauses.begin() + i);
                add = false;
                break;
            }
        }
        if (add)
        {
            i++;
        }
    }

    for (long unsigned int i = 0; i < f.clauses.size(); i++)
    {
        for (long unsigned int j = 0; j < f.clauses[i].size();)
        {
            if (f.clauses[i][j] == -1 * asmt) // if find
            {
                f.clauses[i].erase(f.clauses[i].begin() + j);
                break;
            }
            else
            {
                j++;
            }
        }
    }

    for (long unsigned int i = 0; i < f.clauses.size(); i++)
    {
        if (f.clauses[i].size() == 1)
        {
            this->bcp(f, f.clauses[i][0]);
            break;
        }
    }

    return this->judge_is_satisfied(f);
}

/**
 * @brief dpll
 *
 * @param f input formular
 * @return int the result of dpll
 */
int DPLL::recursive_dpll(Formular f, int asmt)
{
    Formular temp(f);                   // copy the formular
    int result = this->bcp(temp, asmt); // bcp transform
    if (result == status::sat)
    {
        return status::sat;
    }
    else if (result == status::unsat)
    {
        return status::unsat;
    }

    // if the condition is move on, try to assign the value of it
    int var = this->choose_value(temp);

    result = this->recursive_dpll(temp, var);
    if (result == status::sat)
    {
        return status::sat;
    }
    else
    {
        return this->recursive_dpll(temp, -1 * var);
    }

    return status::unsat;
}

// judge whether the formular is satisfied
int DPLL::judge_is_satisfied(Formular f) const
{
    std::vector<std::vector<int>> clauses = f.clauses;
    std::vector<int> single_lit;

    if (clauses.size() == 0)
    {
        return status::sat;
    }

    for (long unsigned int i = 0; i < clauses.size(); i++) // check if there is empty clauses
    {
        if (clauses[i].size() == 0)
        {
            return status::unsat;
        }

        if (clauses[i].size() == 1)
        {
            single_lit.push_back(clauses[i][0]);
        }
    }

    // check if there is Opposite number
    for (long unsigned int i = 0; i < single_lit.size(); i++)
    {
        for (long unsigned int j = i + 1; j < single_lit.size(); j++)
        {
            if (single_lit[i] == -1 * single_lit[j])
            {
                return status::unsat;
            }
        }
    }

    return status::move_on;
}

int DPLL::choose_value(Formular f) const
{
    std::vector<std::vector<int>> cfn = f.clauses;
    int minist_number = INT16_MAX;
    for (unsigned long int i = 0; i < cfn.size(); i++)
    {
        for (unsigned long int j = 0; j < cfn[i].size(); j++)
        {
            int abs_n = cfn[i][j] > 0 ? cfn[i][j] : -1 * cfn[i][j];
            minist_number = minist_number < abs_n ? minist_number : abs_n;
        }
    }
    return minist_number;
}