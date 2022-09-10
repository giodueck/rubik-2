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
    vec3 GetDim() { return dim; }
    Cubie GetCubie(vec3 pos);

    void Rotate(vec3 r, vec3 faces = vec3(0, 0, 0));
};
