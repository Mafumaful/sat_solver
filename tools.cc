#include "tools.h"

/**
 * @brief remove the space of the string
 *
 * @param line the string to be processed
 */
// a helper function parsing the input into the formula string and the assignment string
void parseLine(std::string &line)
{
    // your code starts here
    // remove the space of the string
    std::string templine = line; // templine is a copy of line but it has no space
    int count = 0;
    for (int i = 0; line[i]; i++)
    {
        if (templine[i] != ' ')
            templine[count++] = templine[i];
    }
    line = templine.substr(0, count);
}
