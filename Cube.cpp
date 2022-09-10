#include "Cube.h"

Cube::Cube()
{
    this->dim = vec3(0, 0, 0);
}

Cube::Cube(vec3 dim)
{
    this->dim = dim;
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                this->cubies.push_back(Cubie(dim, vec3(i, j, k)));
            }
        }
    }
}

Cube::~Cube()
{
}

Cubie Cube::GetCubie(vec3 pos)
{
    return cubies[pos.x * dim.y * dim.z + pos.y * dim.z + pos.z];
}
