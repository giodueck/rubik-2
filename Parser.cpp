#include <string>
#include <cstring>
#include <vector>
#include "Parser.h"
#include "Cube.h"

void Parser::Move(Cube &cube, char mov, char mod, int &ctr)
{
    switch (mov)
    {
        case 'R':
            cube.R(mod);
            ctr++;
            break;
        case 'L':
            cube.L(mod);
            ctr++;
            break;
        case 'U':
            cube.U(mod);
            ctr++;
            break;
        case 'D':
            cube.D(mod);
            ctr++;
            break;
        case 'F':
            cube.F(mod);
            ctr++;
            break;
        case 'B':
            cube.B(mod);
            ctr++;
            break;
        case 'M':
            cube.M(mod);
            ctr += 2;
            break;
        case 'E':
            cube.E(mod);
            ctr += 2;
            break;
        case 'S':
            cube.S(mod);
            ctr += 2;
            break;
        case 'X':
            cube.X(mod);
            break;
        case 'Y':
            cube.Y(mod);
            break;
        case 'Z':
            cube.Z(mod);
            break;
    }
}

void Parser::Move(Cube &cube, std::string str, int &ctr)
{
    // Interprets a move from a string and calls the other move
    char mov = 0, mod = 0;

    switch (str[1])
    {
        case '\'':
            mod = -1;
            break;
        case '2':
            mod = 2;
            break;
        case ' ': case '\0': case '\t': case '\n':
            mod = 1;
            break;
        default:
            throw "Bad move: " + str[1];
    }

    switch (str[0])
    {
        case 'R':
            cube.R(mod);
            ctr++;
            break;
        case 'L':
            cube.L(mod);
            ctr++;
            break;
        case 'U':
            cube.U(mod);
            ctr++;
            break;
        case 'D':
            cube.D(mod);
            ctr++;
            break;
        case 'F':
            cube.F(mod);
            ctr++;
            break;
        case 'B':
            cube.B(mod);
            ctr++;
            break;
        case 'M':
            cube.M(mod);
            ctr += 2;
            break;
        case 'E':
            cube.E(mod);
            ctr += 2;
            break;
        case 'S':
            cube.S(mod);
            ctr += 2;
            break;
        case 'X':
            cube.X(mod);
            break;
        case 'Y':
            cube.Y(mod);
            break;
        case 'Z':
            cube.Z(mod);
            break;
        default:
            throw "Bad move: " + str[0];
    }
}

void Parser::Parse(Cube &cube, std::string str, int &ctr)
{
    // Tokenizes str and evaluates each resulting move substring
    std::vector<char*> moves;
    char* aux;
    const char* delim = " \n";

    char *cstr = (char*) malloc(sizeof(char) * (str.length() + 1));
    strcpy(cstr, str.c_str());

    aux = strtok(cstr, " \n");
    if (aux) moves.push_back(aux);

    while (aux)
    {
        aux = strtok(NULL, " \n");
        if (aux) moves.push_back(aux);
    }

    for (int i = 0; i < moves.size(); i++)
    {
        Parser::Move(cube, moves[i], ctr);
    }

    free(cstr);
}

// Executes the first move described in string move if valid,
// else throws an exception
void Parser::Move(CompacterCube &cc, std::string str, int &ctr)
{
    // Interprets a move from a string and calls the other move
    char mov = 0, mod = 0;

    switch (str[1])
    {
        case '\'':
            mod = -1;
            break;
        case '2':
            mod = 2;
            break;
        case ' ': case '\0': case '\t': case '\n':
            mod = 1;
            break;
        default:
            throw "Bad move: " + str[1];
    }

    switch (str[0])
    {
        case 'R':
            CCube::R(cc, mod);
            ctr++;
            break;
        case 'L':
            CCube::L(cc, mod);
            ctr++;
            break;
        case 'U':
            CCube::U(cc, mod);
            ctr++;
            break;
        case 'D':
            CCube::D(cc, mod);
            ctr++;
            break;
        case 'F':
            CCube::F(cc, mod);
            ctr++;
            break;
        case 'B':
            CCube::B(cc, mod);
            ctr++;
            break;
        case 'M':
            CCube::M(cc, mod);
            ctr += 2;
            break;
        case 'E':
            CCube::E(cc, mod);
            ctr += 2;
            break;
        case 'S':
            CCube::S(cc, mod);
            ctr += 2;
            break;
        case 'X':
            CCube::X(cc, mod);
            break;
        case 'Y':
            CCube::Y(cc, mod);
            break;
        case 'Z':
            CCube::Z(cc, mod);
            break;
        default:
            throw "Bad move: " + str[0];
    }
}

// Tokenize string and execute moves. str has to be tokenizable by ' '.
void Parser::Parse(CompacterCube &cc, std::string str, int &ctr)
{
    // Tokenizes str and evaluates each resulting move substring
    std::vector<char*> moves;
    char* aux;
    const char* delim = " \n";

    char *cstr = (char*) malloc(sizeof(char) * (str.length() + 1));
    strcpy(cstr, str.c_str());

    aux = strtok(cstr, " \n");
    if (aux) moves.push_back(aux);

    while (aux)
    {
        aux = strtok(NULL, " \n");
        if (aux) moves.push_back(aux);
    }

    for (int i = 0; i < moves.size(); i++)
    {
        Parser::Move(cc, moves[i], ctr);
    }

    free(cstr);
}
