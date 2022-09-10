#pragma once

#include "Position.h"

/*
    Cubies get initialized with a position, which dictates what kind of piece it is and
    which sides get which color.

    Corner (0, 0, 0) is the Green, White, Orange corner, with White on top and Green in front.
    X along White-Green
    Y along Green-Orange
    Z along White-Orange
*/

class Cubie
{
public:
    enum Color sides[6];

    Cubie() {};
    Cubie(vec3 dim, vec3 pos);
    ~Cubie();

    void Rotate(vec3 r);
};
