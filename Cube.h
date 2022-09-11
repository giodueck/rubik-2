#pragma once

#include <vector>
#include "Cubie.h"

/*
    CubeCompact3
    Reduced space cube representation for storing in mass.
    
    char cubiePos[27]: Flat 3x3x3 matrix which stores cubie indices, numbered by their position
      in the solved cube. These indices indicate which cubie is in which position. If this
      vector is ordered, the cubies are in the right order, though the cube is not necessarily
      solved.

    char cubieRot[27]: Flat 3x3x3 matrix which stores cubie rotations. It uses the "good edge"
      definition to store edge rotations (0: not good, 1: good). Centers have no possible rotation
      (always 0, can be ignored), and corners have either white or yellow facing up/down, front/back
      or left/right, and only one of any pair (0: U/D, 1: F/B, 2: L/R).
*/
struct CubeCompact3
{
    char cubiePos[27];
    char cubieRot[27];
};

/*
    CubeCompacter3
    Even more reduced space cube representation for storing in mass.

    Can represent the same information in half the space used by a CubeCompact3.

    With 27 cubies in at most 3 rotations, there are 81 possible values for each corner piece, which
    fits into 1 byte.

    Position is representable with 5 bits (27 < 32) and rotation with 2 bits (3 < 4), using a total
    of 7 bits for each piece.

    0 RR PPPPP
*/
struct CubeCompacter3
{
    char cubie[27];
};

class Cube
{
private:
    vec3 dim;
    std::vector<Cubie> cubies;

public:
    Cube();
    Cube(int dim_);
    Cube(struct CubeCompact3 cc3);
    ~Cube();

    vec3 GetDim() { return dim; }
    Cubie GetCubie(vec3 pos);

    struct CubeCompact3 Compact();
    struct CubeCompacter3 Compacter();

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
