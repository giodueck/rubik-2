#pragma once

#include <vector>
#include "Cubie.h"
#include "CCube.h"

class Cube
{
private:
    vec3 dim;
    std::vector<Cubie> cubies;

public:
    Cube();
    Cube(int dim_);
    Cube(CompactCube cc3);
    Cube(CompacterCube cr3);
    ~Cube();

    vec3 GetDim() { return dim; }
    Cubie GetCubie(vec3 pos);

    CompactCube Compact();
    CompacterCube Compacter();

    void Rotate(vec3 r, vec3 faces = vec3(0, 0, 0));

    void X(int dir = 1);
    void Y(int dir = 1);
    void Z(int dir = 1);

    void F(int dir = 1, int depth = 1, bool slice = false);
    void U(int dir = 1, int depth = 1, bool slice = false);
    void R(int dir = 1, int depth = 1, bool slice = false);
    void B(int dir = 1, int depth = 1, bool slice = false);
    void D(int dir = 1, int depth = 1, bool slice = false);
    void L(int dir = 1, int depth = 1, bool slice = false);

    void M(int dir = 1);
    void E(int dir = 1);
    void S(int dir = 1);
};
