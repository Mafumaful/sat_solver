/**
 * An example unit test using doctest. See documentation at
 * https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tseitinTransformer.h"
#include "tools.h"
#include "treeNode.h"

using namespace std;

std::vector<std::vector<int>> assignment(std::vector<std::vector<int>> cnf, int target)
{

    for (int i = 0; i < cnf.size(); i++)
    {
        for (int j = 0; j < cnf[i].size(); j++)
        {

            if (cnf[i][j] == target) // if find
            {
                cnf.erase(cnf.begin() + i);
                i--;
            }
        }
    }

    for (int i = 0; i < cnf.size(); i++)
    {
        for (int j = 0; j < cnf[i].size(); j++)
        {

            if (cnf[i][j] == -1 * target) // if find
            {
                cnf[i].erase(cnf[i].begin() + j);
                j--;
            }
        }
    }

    return cnf;
}

TEST_CASE("default")
{
    vector<vector<int>> a;
    vector<int> b;
    b = {-1, 2};
    a.push_back(b);
    b.clear();
    b = {-1, 2};
    a.push_back(b);
    b.clear();
    b = {-2, -2, 1};
    a.push_back(b);
    b.clear();
    b = {1};
    a.push_back(b);

    for (int i = 0; i < a.size(); i++)
    {
        cout << "[ ";
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << " " << a[i][j];
        }
        cout << " ]" << endl;
    }

    cout << endl;
    std::vector<std::vector<int>> last = assignment(a, 2);
    for (int i = 0; i < last.size(); i++)
    {
        cout << "[ ";
        for (int j = 0; j < last[i].size(); j++)
        {
            cout << " " << last[i][j];
        }
        cout << " ]" << endl;
    }
}