#pragma once

/*
    CompactCube
    Reduced space (54B) cube representation for storing in mass.
    
    char cubiePos[27]: Flat 3x3x3 matrix which stores cubie indices, numbered by their position
      in the solved cube. These indices indicate which cubie is in which position. If this
      vector is ordered, the cubies are in the right positions, though the cube is not necessarily
      solved.
      Position (0, 0, 0) is FLU, (0, 0, 2) is BLU, (0, 2, 2) is BLD, (2, 2, 2) is BRD

    char cubieRot[27]: Flat 3x3x3 matrix which stores cubie rotations. It uses the "good edge"
      definition to store edge rotations (0: not good, 1: good). Centers have no possible rotation
      (always 0, can be ignored), and corners have either white or yellow facing up/down, front/back
      or left/right (0: U/D, 1: F/B, 2: L/R).
    
    Not used in practice because position and rotation can easily be merged into one byte, making
    an implementation for this format not necessary.
*/
typedef struct CompactCube
{
    char cubiePos[27];
    char cubieRot[27];
} CompactCube;

/*
    CompacterCube
    Even more reduced space (27B) cube representation for storing in mass.

    Can represent the same information in half the space used by a CubeCompact3.

    With 27 cubies in at most 3 rotations, there are 81 possible values for each piece, which
    fits into 1 byte.

    Position is representable with 5 bits (27 < 32) and rotation with 2 bits (3 < 4), using a total
    of 7 bits for each piece.

    0 RR PPPPP
*/
typedef struct CompacterCube
{
    char cubie[27];
} CompacterCube;

namespace CCube
{
    void X(CompacterCube &cc, int dir = 1);
    void Y(CompacterCube &cc, int dir = 1);
    void Z(CompacterCube &cc, int dir = 1);

    void F(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    void U(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    void R(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    void B(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    void D(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    void L(CompacterCube &cc, int dir = 1, int depth = 1, bool slice = false);
    
    void M(CompacterCube &cc, int dir = 1);
    void E(CompacterCube &cc, int dir = 1);
    void S(CompacterCube &cc, int dir = 1);
}