#include "CCube.h"

namespace CCube
{
    // Create solved CompacterCube
    CCube_t SolvedCube()
    {
        CCube_t ret;
        for (int i = 0; i < 27; i++)
            ret.cubie[i] = i;
        return ret;
    }

    // Create scrambled CompacterCube, a NULL or empty string produces a random 40 move scramble
    CCube_t ScrambledCube(std::string scramble)
    {
        return SolvedCube();
    }

    // Turn the cube on the R face
    void X(CCube_t &cc, int dir)
    {
        CCube_t r;
        if (dir == 1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                // x, i, j, k are used to describe the initial and final indices of pieces
                // and how they move around the cube representation with a cube rotation.
                // This relationship depends on if the cube is rotated clockwise or anticlockwise.
                x = 6 + 9 * i;
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 3 * k];
                        // Some pieces get rotated in the cube representation, in this case
                        // four edges and all corners, depending on initial rotation.
                        // See how rotation is represented in the type definition for CCube_t
                        switch (i * 9 + j * 3 + k)
                        {
                            case 9: case 11: case 15: case 17:
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[i * 9 + j * 3 + k] >> 5 != 2)
                                    r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                                break;
                            default:
                                break;
                        }
                    }
                    x++;
                }
            }
        } else if (dir == -1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 + 9 * i;
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[x - 3 * k] = cc.cubie[i * 9 + j * 3 + k];
                        switch (x - 3 * k)
                        {
                            case 9: case 11: case 15: case 17:
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[x - 3 * k] >> 5 != 2)
                                    r.cubie[x - 3 * k] ^= 0x20;
                                break;
                            default:
                                break;
                        }
                    }
                    x++;
                }
            }
        } else if (dir == 2)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    r.cubie[i * 9 + j] = cc.cubie[(i + 1) * 9 - j - 1];
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the cube on the U face
    void Y(CCube_t &cc, int dir)
    {
        CCube_t r;
        if (dir == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int x = 18 + i + 3 * j;
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 9 * k];
                        switch (i * 9 + j * 3 + k)
                        {
                            case 3: case 5: case 21: case 23:
                                r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                                break;
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[i * 9 + j * 3 + k] >> 5)
                                    r.cubie[i * 9 + j * 3 + k] ^= 0x60;
                            default:
                                break;
                        }
                    }
                }
            }
        } else if (dir == -1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int x = 18 + i + 3 * j;
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[x - 9 * k] = cc.cubie[i * 9 + j * 3 + k];
                        switch (x - 9 * k)
                        {
                            case 3: case 5: case 21: case 23:
                                r.cubie[x - 9 * k] ^= 0x20;
                                break;
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[x - 9 * k] >> 5)
                                    r.cubie[x - 9 * k] ^= 0x60;
                            default:
                                break;
                        }
                    }
                }
            }
        } else if (dir == 2)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 21 - 9 * i - 6;
                for (int j = 0; j < 3; j++)
                {
                    x += 6;
                    for (int k = 0; k < 3; k++)
                    {
                        x--;
                        r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                    }
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the cube on the F face
    void Z(CCube_t &cc, int dir)
    {
        CCube_t r;
        if (dir == 1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[i * 9 + j * 3 + k] = cc.cubie[x++];
                        if ((i * 9 + j * 3 + k) % 2)
                        {
                            r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                        } else switch (i * 9 + j * 3 + k)
                        {
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[i * 9 + j * 3 + k] >> 5 != 1)
                                    r.cubie[i * 9 + j * 3 + k] ^= 0x40;
                                break;
                            default:
                                break;
                        }
                    }
                    x += 6;
                }
            }
        } else if (dir == -1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        r.cubie[x] = cc.cubie[i * 9 + j * 3 + k];
                        if (x % 2)
                        {
                            r.cubie[x] ^= 0x20;
                        } else switch (x)
                        {
                            case 0: case 2: case 6: case 8:
                            case 18: case 20: case 24: case 26:
                                if (r.cubie[x] >> 5 != 1)
                                    r.cubie[x] ^= 0x40;
                                break;
                            default:
                                break;
                        }
                        x++;
                    }
                    x += 6;
                }
            }
        } else if (dir == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                int x = 24 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    r.cubie[i * 3 + j] = cc.cubie[x++];
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the F face
    void F(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == 1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 0;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                    if ((i * 9 + j * 3 + k) % 2)
                    {
                        r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                    } else switch (i * 9 + j * 3 + k)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 1)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 9;
                }
            }
        } else if (dir == -1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 0;
                    r.cubie[x] = cc.cubie[i * 9 + j * 3 + k];
                    if (x % 2)
                    {
                        r.cubie[x] ^= 0x20;
                    } else switch (x)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x] >> 5 != 1)
                                r.cubie[x] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 9;
                }
            }
        } else if (dir == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                r.cubie[i * 3] = cc.cubie[24 - i * 3];
            }
        }
        else return;
        cc = r;
    }

    // Turn the U face
    void U(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 0;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 9 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 3: case 5: case 21: case 23:
                            r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x60;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == -1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 0;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 9 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 9 * k)
                    {
                        case 3: case 5: case 21: case 23:
                            r.cubie[x - 9 * k] ^= 0x20;
                            break;
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x - 9 * k] >> 5)
                                r.cubie[x - 9 * k] ^= 0x60;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == 2)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 21 - 9 * i - 6;
                int j = 0;
                x += 6;
                for (int k = 0; k < 3; k++)
                {
                    x--;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the R face
    void R(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == 1)
        {
            int x;
            int i = 2;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 3 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 2)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == -1)
        {
            int x;
            int i = 2;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 3 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 3 * k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x - 3 * k] >> 5 != 2)
                                r.cubie[x - 3 * k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == 2)
        {
            int i = 2;
            for (int j = 0; j < 9; j++)
            {
                r.cubie[i * 9 + j] = cc.cubie[(i + 1) * 9 - j - 1];
            }
        }
        else return;
        cc = r;
    }

    // Turn the B face
    void B(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == -1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 2;
                    x += 2;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                    if ((i * 9 + j * 3 + k) % 2)
                    {
                        r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                    } else switch (i * 9 + j * 3 + k)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 1)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 7;
                }
            }
        } else if (dir == 1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 2;
                    x += 2;
                    r.cubie[x] = cc.cubie[i * 9 + j * 3 + k];
                    if (x % 2)
                    {
                        r.cubie[x] ^= 0x20;
                    } else switch (x)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x] >> 5 != 1)
                                r.cubie[x] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 7;
                }
            }
        } else if (dir == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                int x = 26 - i * 3;
                r.cubie[i * 3 + 2] = cc.cubie[x];
            }
        }
        else return;
        cc = r;
    }

    // Turn the D face
    void D(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == -1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 2;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 9 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 3: case 5: case 21: case 23:
                            r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x60;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 2;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 9 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 9 * k)
                    {
                        case 3: case 5: case 21: case 23:
                            r.cubie[x - 9 * k] ^= 0x20;
                            break;
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x - 9 * k] >> 5)
                                r.cubie[x - 9 * k] ^= 0x60;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == 2)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 21 - 9 * i - 6;
                int j = 2;
                x += 12;
                for (int k = 0; k < 3; k++)
                {
                    x--;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the L face
    void L(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == -1)
        {
            int x;
            int i = 0;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 3 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 2)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == 1)
        {
            int x;
            int i = 0;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 3 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 3 * k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x - 3 * k] >> 5 != 2)
                                r.cubie[x - 3 * k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == 2)
        {
            int i = 0;
            for (int j = 0; j < 9; j++)
            {
                r.cubie[i * 9 + j] = cc.cubie[(i + 1) * 9 - j - 1];
            }
        }
        else return;
        cc = r;
    }

    
    // Turn the vertical slice on x = 1
    void M(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == -1)
        {
            int x;
            int i = 1;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 3 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 2)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == 1)
        {
            int x;
            int i = 1;
            x = 6 + 9 * i;
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 3 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 3 * k)
                    {
                        case 9: case 11: case 15: case 17:
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x - 3 * k] >> 5 != 2)
                                r.cubie[x - 3 * k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
                x++;
            }
        } else if (dir == 2)
        {
            int i = 1;
            for (int j = 0; j < 9; j++)
            {
                r.cubie[i * 9 + j] = cc.cubie[(i + 1) * 9 - j - 1];
            }
        }
        else return;
        cc = r;
    }

    // Turn the horizontal slice on y = 1
    void E(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == -1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 1;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x - 9 * k];
                    switch (i * 9 + j * 3 + k)
                    {
                        case 0x03: case 0x05: case 0x15: case 0x17:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 2)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == 1)
        {
            for (int i = 0; i < 3; i++)
            {
                int j = 1;
                int x = 18 + i + 3 * j;
                for (int k = 0; k < 3; k++)
                {
                    r.cubie[x - 9 * k] = cc.cubie[i * 9 + j * 3 + k];
                    switch (x - 9 * k)
                    {
                        case 0x03: case 0x05: case 0x15: case 0x17:
                            if (r.cubie[x - 9 * k] >> 5 != 2)
                                r.cubie[x - 9 * k] ^= 0x20;
                            break;
                        default:
                            break;
                    }
                }
            }
        } else if (dir == 2)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 21 - 9 * i - 6;
                int j = 1;
                x += 9;
                for (int k = 0; k < 3; k++)
                {
                    x--;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                }
            }
        }
        else return;
        cc = r;
    }

    // Turn the vertical slice on z = 1
    void S(CCube_t &cc, int dir)
    {
        CCube_t r = cc;
        if (dir == 1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 1;
                    x += 1;
                    r.cubie[i * 9 + j * 3 + k] = cc.cubie[x];
                    if ((i * 9 + j * 3 + k) % 2)
                    {
                        r.cubie[i * 9 + j * 3 + k] ^= 0x20;
                    } else switch (i * 9 + j * 3 + k)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[i * 9 + j * 3 + k] >> 5 != 1)
                                r.cubie[i * 9 + j * 3 + k] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 8;
                }
            }
        } else if (dir == -1)
        {
            int x;
            for (int i = 0; i < 3; i++)
            {
                x = 6 - i * 3;
                for (int j = 0; j < 3; j++)
                {
                    int k = 1;
                    x += 1;
                    r.cubie[x] = cc.cubie[i * 9 + j * 3 + k];
                    if (x % 2)
                    {
                        r.cubie[x] ^= 0x20;
                    } else switch (x)
                    {
                        case 0: case 2: case 6: case 8:
                        case 18: case 20: case 24: case 26:
                            if (r.cubie[x] >> 5 != 1)
                                r.cubie[x] ^= 0x40;
                            break;
                        default:
                            break;
                    }
                    x += 8;
                }
            }
        } else if (dir == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                int x = 25 - i * 3;
                r.cubie[i * 3 + 1] = cc.cubie[x];
            }
        }
        else return;
        cc = r;
    }

}