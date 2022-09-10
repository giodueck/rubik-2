#include "Cube.h"

Cube::Cube()
{
    this->dim = vec3(0, 0, 0);
}

Cube::Cube(vec3 dim)
{
    if (dim.x != dim.y || dim.y != dim.z)
        throw "Only NxNxN cubes work properly!";
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

void Cube::Rotate(vec3 r, vec3 faces)
{
    if (r.x && r.y || r.x && r.z || r.y && r.z)
        throw "Rotations can only be on 1 axis at a time!";
    
    std::vector<Cubie> cubies_c;
    cubies_c.insert(cubies_c.begin(), cubies.begin(), cubies.end());
    if (r.x) // rotate with respect to right face
    {
        switch (r.x % 4)
        {
        case 1: case -3:
            for (int i = 0; i < dim.x; i++)
            {
                if (i < faces.x || i - dim.x + 1 > faces.x || faces.x == 0)
                    for (int j = 0; j < dim.y; j++)
                    {
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[i * dim.y * dim.z + (dim.z - 1 - k) * dim.z + j];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
            }
            break;
        case 2: case -2:
            for (int i = 0; i < dim.x; i++)
            {
                if (i < faces.x || i - dim.x + 1 > faces.x || faces.x == 0)
                    for (int j = 0; j < dim.y; j++)
                    {
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[i * dim.y * dim.z + (dim.y - 1 - j) * dim.z + (dim.z - 1 - k)];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
            }
            break;
        case 3: case -1:
            for (int i = 0; i < dim.x; i++)
            {
                if (i < faces.x || i - dim.x + 1 > faces.x || faces.x == 0)
                    for (int j = 0; j < dim.y; j++)
                    {
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[i * dim.y * dim.z + k * dim.z + (dim.y - 1 - j)];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
            }
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
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    if (j < faces.y || j - dim.y + 1 > faces.y || faces.y == 0)
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[(dim.z - 1 - k) * dim.y * dim.z + j * dim.z + i];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                }
            }
            break;
        case 2: case -2:
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    if (j < faces.y || j - dim.y + 1 > faces.y || faces.y == 0)
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[(dim.x - 1 - i) * dim.y * dim.z + j * dim.z + (dim.z - 1 - k)];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                }
            }
            break;
        case 3: case -1:
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    if (j < faces.y || j - dim.y + 1 > faces.y || faces.y == 0)
                        for (int k = 0; k < dim.z; k++)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[k * dim.y * dim.z + j * dim.z + (dim.x - 1 - i)];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                }
            }
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
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    for (int k = 0; k < dim.z; k++)
                    {
                        if (k < faces.z || k - dim.z + 1 > faces.z || faces.z == 0)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[j * dim.y * dim.z + (dim.x - 1 - i) * dim.z + k];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
                }
            }
            break;
        case 2: case -2:
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    for (int k = 0; k < dim.z; k++)
                    {
                        if (k < faces.z || k - dim.z + 1 > faces.z || faces.z == 0)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[(dim.x - 1 - i) * dim.y * dim.z + (dim.y - 1 - j) * dim.z + k];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
                }
            }
            break;
        case 3: case -1:
            for (int i = 0; i < dim.x; i++)
            {
                for (int j = 0; j < dim.y; j++)
                {
                    for (int k = 0; k < dim.z; k++)
                    {
                        if (k < faces.z || k - dim.z + 1 > faces.z || faces.z == 0)
                        {
                            cubies[i * dim.y * dim.z + j * dim.z + k] = cubies_c[(dim.y - 1 - j) * dim.y * dim.z + i * dim.z + k];
                            cubies[i * dim.y * dim.z + j * dim.z + k].Rotate(r);
                        }
                    }
                }
            }
            break;
        
        default:
            break;
        }
    }
}

void Cube::X(int dir)
{
    this->Rotate(vec3(dir, 0, 0));
}

void Cube::Y(int dir)
{
    this->Rotate(vec3(0, dir, 0));
}

void Cube::Z(int dir)
{
    this->Rotate(vec3(0, 0, dir));
}

void Cube::F(int dir, int depth, bool slice)
{
    this->Rotate(vec3(0, 0, dir), vec3(0, 0, depth));
    if (slice)
        this->Rotate(vec3(0, 0, -dir), vec3(0, 0, (depth > 0 ? depth - 1 : depth + 1)));
}

void Cube::U(int dir, int depth, bool slice)
{
    this->Rotate(vec3(0, dir, 0), vec3(0, depth, 0));
    if (slice)
        this->Rotate(vec3(0, -dir, 0), vec3(0, (depth > 0 ? depth - 1 : depth + 1), 0));
}

void Cube::R(int dir, int depth, bool slice)
{
    this->Rotate(vec3(dir, 0, 0), vec3(-depth, 0, 0));
    if (slice)
        this->Rotate(vec3(-dir, 0, 0), vec3(-(depth > 0 ? depth - 1 : depth + 1), 0, 0));
}

void Cube::B(int dir, int depth, bool slice)
{
    this->Rotate(vec3(0, 0, -dir), vec3(0, 0, -depth));
    if (slice)
        this->Rotate(vec3(0, 0, dir), vec3(0, 0, -(depth > 0 ? depth - 1 : depth + 1)));
}

void Cube::D(int dir, int depth, bool slice)
{
    this->Rotate(vec3(0, -dir, 0), vec3(0, -depth, 0));
    if (slice)
        this->Rotate(vec3(0, dir, 0), vec3(0, -(depth > 0 ? depth - 1 : depth + 1), 0));
}

void Cube::L(int dir, int depth, bool slice)
{
    this->Rotate(vec3(-dir, 0, 0), vec3(depth, 0, 0));
    if (slice)
        this->Rotate(vec3(dir, 0, 0), vec3((depth > 0 ? depth - 1 : depth + 1), 0, 0));
}

void Cube::M(int dir)
{
    this->Rotate(vec3(-dir, 0, 0), vec3(-this->dim.x + 1, 0, 0));
    this->Rotate(vec3(dir, 0, 0), vec3(-1, 0, 0));
}

void Cube::E(int dir)
{
    this->Rotate(vec3(0, -dir, 0), vec3(0, -this->dim.x + 1, 0));
    this->Rotate(vec3(0, dir, 0), vec3(0, -1, 0));
}

void Cube::S(int dir)
{
    this->Rotate(vec3(0, 0, dir), vec3(0, 0, -this->dim.x + 1));
    this->Rotate(vec3(0, 0, -dir), vec3(0, 0, -1));
}
