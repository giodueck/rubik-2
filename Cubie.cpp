#include "Cubie.h"

Cubie::Cubie(vec3 dim, vec3 pos)
{
    // corner if 3 pos components are 0 or max
    // edge if 2
    // center if 1
    // core if none, core cubies are not visible

    for (int i = 0; i < 6; i++)
        sides[i] = NONE;
    
    if (pos.x == 0)
        sides[ORANGE] = ORANGE;
    if (pos.x == dim.x - 1)
        sides[RED] = RED;
    
    if (pos.y == 0)
        sides[WHITE] = WHITE;
    if (pos.y == dim.y - 1)
        sides[YELLOW] = YELLOW;
    
    if (pos.z == 0)
        sides[GREEN] = GREEN;
    if (pos.z == dim.z - 1)
        sides[BLUE] = BLUE;
}

Cubie::~Cubie()
{
}
