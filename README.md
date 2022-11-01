# Rubik 2
A new iteration of a Rubik's cube solver, this time with a cube built on cubies, individual unit cubes with colored faces, instead of my previous approach of just colored faces.

This allows the cube to take any XxYxZ dimension, not just 3x3x3.

Designed to be usable with various solvers, primarily with bidirectional search but open for experimentation.

## Rubik's Cube Solver 2: Algorithmic Boogaloo
Using the Parser and Cube classes and -O2 compilation, it takes somewhere around 14.2 seconds to execute 50M moves, not very fast but also using high level representations of the cube.

If a parser for moves using the compressed structures could be made, it may be orders of magnitude faster and allow for limited bruteforcing and still finding solutions fast using human algorithms.