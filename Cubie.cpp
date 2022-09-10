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

void Cubie::Rotate(vec3 r)
{
    if (r.x && r.y || r.x && r.z || r.y && r.z)
        throw "Rotations can only be on 1 axis at a time!";
    
    enum Color aux;
    if (r.x) // rotate with respect to right face
    {
        switch (r.x % 4)
        {
        case 1: case -3:
            // clockwise
            // U -> B -> D -> F -> U
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[YELLOW];
            this->sides[YELLOW] = this->sides[BLUE];
            this->sides[BLUE] = this->sides[WHITE];
            this->sides[WHITE] = aux;
            break;
        case 2: case -2:
            // double
            // U -> D -> U, F -> B -> F
            aux = this->sides[WHITE];
            this->sides[WHITE] = this->sides[YELLOW];
            this->sides[YELLOW] = aux;
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[BLUE];
            this->sides[BLUE] = aux;
            break;
        case 3: case -1:
            // counterclockwise
            // U -> F -> D -> B -> U
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[WHITE];
            this->sides[WHITE] = this->sides[BLUE];
            this->sides[BLUE] = this->sides[YELLOW];
            this->sides[YELLOW] = aux;
            break;
        
        default:
            break;
        }
    }
    else if (r.y) // rotate with respect to up face
    {
        switch (r.y % 4)
        {
        case 1: case -3:
            // clockwise
            // F -> R -> B -> L -> F
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[RED];
            this->sides[RED] = this->sides[BLUE];
            this->sides[BLUE] = this->sides[ORANGE];
            this->sides[ORANGE] = aux;
            break;
        case 2: case -2:
            // double
            // R -> L -> R, F -> B -> F
            aux = this->sides[RED];
            this->sides[RED] = this->sides[ORANGE];
            this->sides[ORANGE] = aux;
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[BLUE];
            this->sides[BLUE] = aux;
            break;
        case 3: case -1:
            // counterclockwise
            // F -> L -> B -> R -> F
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[ORANGE];
            this->sides[ORANGE] = this->sides[BLUE];
            this->sides[BLUE] = this->sides[RED];
            this->sides[RED] = aux;
            break;
        
        default:
            break;
        }
    }
    else if (r.z) // rotate with respect to front face
    {
        switch (r.z % 4)
        {
        case 1: case -3:
            // clockwise
            // U -> L -> D -> R -> U
            aux = this->sides[WHITE];
            this->sides[WHITE] = this->sides[ORANGE];
            this->sides[ORANGE] = this->sides[YELLOW];
            this->sides[YELLOW] = this->sides[RED];
            this->sides[RED] = aux;
            break;
        case 2: case -2:
            // double
            // R -> L -> R, U -> D -> U
            aux = this->sides[RED];
            this->sides[RED] = this->sides[ORANGE];
            this->sides[ORANGE] = aux;
            aux = this->sides[WHITE];
            this->sides[WHITE] = this->sides[YELLOW];
            this->sides[YELLOW] = aux;
            break;
        case 3: case -1:
            // counterclockwise
            // U -> R -> D -> L -> U
            aux = this->sides[GREEN];
            this->sides[GREEN] = this->sides[RED];
            this->sides[RED] = this->sides[BLUE];
            this->sides[BLUE] = this->sides[ORANGE];
            this->sides[ORANGE] = aux;
            break;
        
        default:
            break;
        }
    }
}
