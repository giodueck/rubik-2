#pragma once

enum Color { NONE = -1, GREEN = 0, WHITE = 1, RED = 2, BLUE = 3, YELLOW = 4, ORANGE = 5 };

typedef struct vec3
{
    int x, y, z;
    vec3() { this->x = 0, this->y = 0, this->z = 0; }
    vec3(int x, int y, int z) { this->x = x, this->y = y, this->z = z; }
} vec3;
