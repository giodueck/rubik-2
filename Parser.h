#pragma once

#include "Cube.h"
#include <string>

namespace Parser
{
    /* Currently only supports 3x3x3 */
    // Executes the first move described in string move if valid,
    // else throws an exception
    void Move(Cube &cube, std::string str, int &ctr);

    // Executes the given move if valid, does nothing if invalid
    void Move(Cube &cube, char mov, char mod, int &ctr);

    // Tokenize string and execute moves. str has to be tokenizable by ' '.
    void Parse(Cube &cube, std::string str, int &ctr);

    /* Parser using compacter cube struct */
    // Executes the first move described in string move if valid,
    // else throws an exception
    void Move(CompacterCube &cc, std::string str, int &ctr);

    // Tokenize string and execute moves. str has to be tokenizable by ' '.
    void Parse(CompacterCube &cc, std::string str, int &ctr);
};