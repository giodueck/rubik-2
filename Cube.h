#pragma once

#include <vector>
#include "Cubie.h"

class Cube
{
private:
    vec3 dim;
    std::vector<Cubie> cubies;
public:
    Cube();
    Cube(vec3 dim);
    ~Cube();
};
