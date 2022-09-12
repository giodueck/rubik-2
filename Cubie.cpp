#include "Cubie.h"

Cubie::Cubie(int dim, vec3 pos)
{
    // corner if 3 pos components are 0 or max
    // edge if 2
    // center if 1
    // core if none, core cubies are not visible

    for (int i = 0; i < 6; i++)
        sides[i] = NONE;
    
    if (pos.x == 0)
        sides[ORANGE] = ORANGE;
    if (pos.x == dim - 1)
        sides[RED] = RED;
    
    if (pos.y == 0)
        sides[WHITE] = WHITE;
    if (pos.y == dim - 1)
        sides[YELLOW] = YELLOW;
    
    if (pos.z == 0)
        sides[GREEN] = GREEN;
    if (pos.z == dim - 1)
        sides[BLUE] = BLUE;
}

Cubie::Cubie(int dim, const vec3 pos, char idx, char rot)
{
    vec3 p;
    p.z = idx % dim;
    idx -= p.z;
    idx /= 3;
    p.y = idx % dim;
    idx -= p.y;
    p.x = idx / 3;
    int faces = (p.x == 0 || p.x == dim - 1) + (p.y == 0 || p.y == dim - 1) + (p.z == 0 || p.z == dim - 1);

    for (int i = 0; i < 6; i++)
        sides[i] = NONE;
    
    if (p.x == 0)
        sides[ORANGE] = ORANGE;
    if (p.x == dim - 1)
        sides[RED] = RED;
    
    if (p.y == 0)
        sides[WHITE] = WHITE;
    if (p.y == dim - 1)
        sides[YELLOW] = YELLOW;
    
    if (p.z == 0)
        sides[GREEN] = GREEN;
    if (p.z == dim - 1)
        sides[BLUE] = BLUE;
    
    // The piece might have a colored side inside the cube, rotate to have all
    // faces on the outside for the given position pos

    // up/down layers
    if (pos.y == 0 || pos.y == dim - 1)
    {
        // orient any face to the top or bottom
        if (pos.y == 0)
        {
            while (sides[WHITE] == NONE)
            {
                Rotate(vec3(1, 0, 0));
                if (sides[WHITE] == NONE)
                    Rotate(vec3(0, 0, 1));
            }
        } else if (pos.y == dim - 1)
        {
            while (sides[YELLOW] == NONE)
            {
                Rotate(vec3(1, 0, 0));
                if (sides[YELLOW] == NONE)
                    Rotate(vec3(0, 0, 1));
            }
        }

        if (faces == 1) // center pieces need no further orientation
            return;
        
        // orient all side-faces of top/bottom pieces
        while ((int)(pos.z == 0 && sides[GREEN] != NONE) + (int)(pos.z == dim - 1 && sides[BLUE] != NONE)
        + (int)(pos.x == 0 && sides[ORANGE] != NONE) + (int)(pos.x == dim - 1 && sides[RED] != NONE) != faces - 1)
        {
            Rotate(vec3(0, 1, 0));
        }
    }

    // middle layer
    else
    {
        // orient any side to the front/back, or to the sides (only if the piece is a L/R center)
        if (pos.z == 0)
        {
            while (sides[GREEN] == NONE)
            {
                Rotate(vec3(1, 0, 0));
                if (sides[GREEN] == NONE)
                    Rotate(vec3(0, 1, 0));
            }
        } else if (pos.z == dim - 1)
        {
            while (sides[BLUE] == NONE)
            {
                Rotate(vec3(1, 0, 0));
                if (sides[BLUE] == NONE)
                    Rotate(vec3(0, 1, 0));
            }
        } else if (pos.x == 0)
        {
            while (sides[ORANGE] == NONE)
            {
                Rotate(vec3(0, 0, 1));
                if (sides[ORANGE] == NONE)
                    Rotate(vec3(0, 1, 0));
            }
        } else if (pos.x == dim - 1)
        {
            while (sides[RED] == NONE)
            {
                Rotate(vec3(0, 0, 1));
                if (sides[RED] == NONE)
                    Rotate(vec3(0, 1, 0));
            }
        }

        if (faces <= 1) // core and center pieces need no further orientation
            return;
        
        // orient all remaining edge pieces
        while ((int)(pos.x == 0 && sides[ORANGE] != NONE) + (int)(pos.x == dim - 1 && sides[RED] != NONE) != faces - 1)
        {
            Rotate(vec3(0, 0, 1));
        }
    }
    
    if (faces == 2) // orient edges
    {
        // check if correct orientation
        bool wy = false;
        char curr_rot = 1;
        for (int l = 0; l < 6 && !wy; l++)
        {
            if (sides[l] == WHITE || sides[l] == YELLOW)
                wy = true;
        }

        // Check for good edges looks at White/Yellow edges one way, and at the other 4 another way, but both are
        // similar checks.
        // This check assumes white on up and green on front, but the centers can be anything, this is
        // simply a representation.
        if (wy)
        {
            if (sides[WHITE] == WHITE || sides[WHITE] == YELLOW || sides[YELLOW] == WHITE || sides[YELLOW] == YELLOW
            || (sides[GREEN] == WHITE || sides[GREEN] == YELLOW || sides[BLUE] == WHITE || sides[BLUE] == YELLOW) && (pos.y != 0 && pos.y != dim - 1))
                curr_rot = 0;
            else
                curr_rot = 1;
        }
        else
        {
            if (sides[WHITE] == GREEN || sides[WHITE] == BLUE || sides[YELLOW] == GREEN || sides[YELLOW] == BLUE
            || (sides[GREEN] == GREEN || sides[GREEN] == BLUE || sides[BLUE] == GREEN || sides[BLUE] == BLUE) && (pos.y != 0 && pos.y != dim - 1))
                curr_rot = 0;
            else
                curr_rot = 1;
        }

        if (curr_rot == rot)
            return;

        // move up pieces into FU, flip, move back
        if (pos.y == 0)
        {
            Rotate(vec3(-1, 0, 0));
            if (pos.z == 0)
                Rotate(vec3(0, 0, 2));
            else if (pos.z < dim - 1)
            {
                Rotate(vec3(0, 0, (pos.x) ? -1 : 1));
                Rotate(vec3(0, (pos.x) ? -1 : 1, 0));
            }
            else
                Rotate(vec3(0, 2, 0));
        }
        // move down pieces into FD, flip, move back
        else if (pos.y == dim - 1)
        {
            Rotate(vec3(1, 0, 0));
            if (pos.z == 0)
                Rotate(vec3(0, 0, 2));
            else if (pos.z < dim - 1)
            {
                Rotate(vec3(0, 0, (pos.x) ? 1 : -1));
                Rotate(vec3(0, (pos.x) ? -1 : 1, 0));
            }
            else
                Rotate(vec3(0, 2, 0));
        }
        // move middle layer pieces to FR, flip, move back
        else
        {
            Rotate(vec3(1, 0, 0));
            if (pos.z == 0)
            {
                Rotate(vec3(0, (pos.x) ? 1 : -1, 0));
                Rotate(vec3(0, 0, (pos.x) ? 1 : -1));
            }
            else
            {
                Rotate(vec3(0, (pos.x) ? -1 : 1, 0));
                Rotate(vec3(0, 0, (pos.x) ? -1 : 1));
            }
        }

        return;
    }

    if (faces == 3) // orient corners
    {
        // move up corners into FRU, orient, move back
        if (pos.y == 0)
        {
            if (pos.x == 0 && pos.z == 0)
                Rotate(vec3(0, -1, 0));
            else if (pos.x == 0)
                Rotate(vec3(0, 2, 0));
            else if (pos.z == dim - 1)
                Rotate(vec3(0, 1, 0));
            
            while (sides[WHITE] != WHITE && sides[WHITE] != YELLOW)
            {
                Rotate(vec3(-1, 0, 0));
                Rotate(vec3(0, 0, -1));
            }

            for (int i = 0; i < rot; i++)
            {
                if (pos.x == pos.z)
                {
                    Rotate(vec3(0, 0, 1));
                    Rotate(vec3(1, 0, 0));
                } else
                {
                    Rotate(vec3(-1, 0, 0));
                    Rotate(vec3(0, 0, -1));
                }
            }

            if (pos.x == 0 && pos.z == 0)
                Rotate(vec3(0, 1, 0));
            else if (pos.x == 0)
                Rotate(vec3(0, 2, 0));
            else if (pos.z == dim - 1)
                Rotate(vec3(0, -1, 0));
        }
        // move down corners into FRD, orient, move back
        else
        {
            if (pos.x == 0 && pos.z == 0)
                Rotate(vec3(0, -1, 0));
            else if (pos.x == 0)
                Rotate(vec3(0, 2, 0));
            else if (pos.z == dim - 1)
                Rotate(vec3(0, 1, 0));
            
            while (sides[YELLOW] != WHITE && sides[YELLOW] != YELLOW)
            {
                Rotate(vec3(1, 0, 0));
                Rotate(vec3(0, 0, 1));
            }

            for (int i = 0; i < rot; i++)
            {
                if (pos.x == pos.z)
                {
                    Rotate(vec3(0, 0, -1));
                    Rotate(vec3(-1, 0, 0));
                } else
                {
                    Rotate(vec3(1, 0, 0));
                    Rotate(vec3(0, 0, 1));
                }
            }

            if (pos.x == 0 && pos.z == 0)
                Rotate(vec3(0, 1, 0));
            else if (pos.x == 0)
                Rotate(vec3(0, 2, 0));
            else if (pos.z == dim - 1)
                Rotate(vec3(0, -1, 0));
        }

        return;
    }
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
            // U -> R -> D -> L -> U
            aux = this->sides[ORANGE];
            this->sides[ORANGE] = this->sides[YELLOW];
            this->sides[YELLOW] = this->sides[RED];
            this->sides[RED] = this->sides[WHITE];
            this->sides[WHITE] = aux;
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
            // U -> L -> D -> R -> U
            aux = this->sides[ORANGE];
            this->sides[ORANGE] = this->sides[WHITE];
            this->sides[WHITE] = this->sides[RED];
            this->sides[RED] = this->sides[YELLOW];
            this->sides[YELLOW] = aux;
            break;
        
        default:
            break;
        }
    }
}
