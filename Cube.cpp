#include "Cube.h"

Cube::Cube()
{
    this->dim = vec3(3, 3, 3);
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                this->cubies.push_back(Cubie(3, vec3(i, j, k)));
            }
        }
    }
}

Cube::Cube(int dim_)
{
    this->dim = vec3(dim_, dim_, dim_);
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                this->cubies.push_back(Cubie(dim_, vec3(i, j, k)));
            }
        }
    }
}

Cube::Cube(CompactCube cc3)
{
    this->dim = vec3(3, 3, 3);
    // construct cubie from position and rotation
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                int idx = i * dim.y * dim.z + j * dim.z + k;
                this->cubies.push_back(Cubie(3, vec3(i, j, k), cc3.cubiePos[idx], cc3.cubieRot[idx]));
            }
        }
    }
}

Cube::Cube(CompacterCube cr3)
{
    this->dim = vec3(3, 3, 3);
    // construct cubie from position and rotation
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                int idx = i * dim.y * dim.z + j * dim.z + k;
                this->cubies.push_back(Cubie(3, vec3(i, j, k), cr3.cubie[idx] & 0x1F, cr3.cubie[idx] >> 5));
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

CompactCube Cube::Compact()
{
    if (dim.x != 3 || dim.y != 3 || dim.z != 3)
        throw "Must be of dimension 3x3x3!";

    CompactCube cc3;
    vec3 idx3;
    int idx;
    Cubie curr;
    for (int i = 0; i < dim.x; i++)
    {
        for (int j = 0; j < dim.y; j++)
        {
            for (int k = 0; k < dim.z; k++)
            {
                idx3 = vec3(1, 1, 1);
                idx = i * dim.y * dim.z + j * dim.z + k;
                curr = this->cubies[idx];

                // Position
                for (int l = 0; l < 6; l++)
                {
                    switch (curr.sides[l])
                    {
                    case GREEN:
                        idx3.z = 0;
                        break;
                    case WHITE:
                        idx3.y = 0;
                        break;
                    case RED:
                        idx3.x = 2;
                        break;
                    case BLUE:
                        idx3.z = 2;
                        break;
                    case YELLOW:
                        idx3.y = 2;
                        break;
                    case ORANGE:
                        idx3.x = 0;
                        break;
                    }
                }
                cc3.cubiePos[idx] = idx3.x * dim.y * dim.z + idx3.y * dim.z + idx3.z;
                
                // Rotation
                    // center or core piece
                if (idx3.x == 1 && idx3.y == 1 || idx3.x == 1 && idx3.z == 1 || idx3.y == 1 && idx3.z == 1)
                {
                    cc3.cubieRot[idx] = 0;
                }
                    // edge piece
                else if (idx3.x == 1 || idx3.y == 1 || idx3.z == 1)
                {
                    bool wy = false;
                    for (int l = 0; l < 6 && !wy; l++)
                    {
                        if (curr.sides[l] == WHITE || curr.sides[l] == YELLOW)
                            wy = true;
                    }

                    // Check for good edges looks at White/Yellow edges one way, and at the other 4 another way, but both are
                    // similar checks.
                    // This check assumes white on up and green on front, but the centers can be anything, this is
                    // simply a representation.
                    if (wy)
                    {
                        if (curr.sides[WHITE] == WHITE || curr.sides[WHITE] == YELLOW || curr.sides[YELLOW] == WHITE || curr.sides[YELLOW] == YELLOW
                        || (curr.sides[GREEN] == WHITE || curr.sides[GREEN] == YELLOW || curr.sides[BLUE] == WHITE || curr.sides[BLUE] == YELLOW) && j == 1)
                            cc3.cubieRot[idx] = 0;
                        else
                            cc3.cubieRot[idx] = 1;
                    }
                    else
                    {
                        if (curr.sides[WHITE] == GREEN || curr.sides[WHITE] == BLUE || curr.sides[YELLOW] == GREEN || curr.sides[YELLOW] == BLUE
                        || (curr.sides[GREEN] == GREEN || curr.sides[GREEN] == BLUE || curr.sides[BLUE] == GREEN || curr.sides[BLUE] == BLUE) && j == 1)
                            cc3.cubieRot[idx] = 0;
                        else
                            cc3.cubieRot[idx] = 1;
                    }
                }

                    // corner pieces
                else
                {
                    // all corner pieces have either white or yellow, check for where it is
                    if (curr.sides[WHITE] == WHITE || curr.sides[WHITE] == YELLOW || curr.sides[YELLOW] == WHITE || curr.sides[YELLOW] == YELLOW)
                        cc3.cubieRot[idx] = 0;
                    else if (curr.sides[GREEN] == WHITE || curr.sides[GREEN] == YELLOW || curr.sides[BLUE] == WHITE || curr.sides[BLUE] == YELLOW)
                        cc3.cubieRot[idx] = 1;
                    else
                        cc3.cubieRot[idx] = 2;
                }
            }
        }
    }

    return cc3;
}

CompacterCube Cube::Compacter()
{
    CompacterCube cr3;
    CompactCube cc3 = Compact();

    for (int i = 0; i < 27; i++)
    {
        cr3.cubie[i] = cc3.cubiePos[i] | cc3.cubieRot[i] << 5;
    }
    
    return cr3;
}