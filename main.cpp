#include <cstdio>

#include "Cube.h"

//Regular background
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

//High intensty background 
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

//Reset
#define COLOR_RESET "\e[0m"

void drawCube(Cube cube)
{
    /*
          U
        L F R B
          D
        
        width:
        z x z x

        height:
        z
        y
        z
     */

    int i, j;
    vec3 dim = cube.GetDim();

    // Top face
    for (i = dim.z - 1; i >= 0; i--)
    {
        for (j = 0; j < dim.z; j++)
            printf("  ");
        for (j = 0; j < dim.x; j++)
        {
            switch (cube.GetCubie(vec3(j, 0, i)).sides[WHITE])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }
        printf("\n");
    }

    // Side, front and back faces
    for (i = 0; i < dim.y; i++)
    {
        // Left
        for (j = dim.z - 1; j >= 0; j--)
        {
            switch (cube.GetCubie(vec3(0, i, j)).sides[ORANGE])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }

        // Front
        for (j = 0; j < dim.x; j++)
        {
            switch (cube.GetCubie(vec3(j, i, 0)).sides[GREEN])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }

        // Right
        for (j = 0; j < dim.z; j++)
        {
            switch (cube.GetCubie(vec3(dim.x - 1, i, j)).sides[RED])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }

        // Back
        for (j = dim.x - 1; j >= 0; j--)
        {
            switch (cube.GetCubie(vec3(j, i, dim.z - 1)).sides[BLUE])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }

        printf("\n");
    }

    // Bottom face
    for (i = 0; i < dim.z; i++)
    {
        for (j = 0; j < dim.z; j++)
            printf("  ");
        for (j = 0; j < dim.x; j++)
        {
            switch (cube.GetCubie(vec3(j, dim.y - 1, i)).sides[YELLOW])
            {
            case GREEN:
                printf(GRNB);
                break;
            case WHITE:
                printf(WHTB);
                break;
            case RED:
                printf(REDB);
                break;
            case BLUE:
                printf(BLUB);
                break;
            case YELLOW:
                printf(YELHB);
                break;
            case ORANGE:
                printf(YELB);
                break;
            
            default:
                printf(COLOR_RESET);
                break;
            }
            printf("  %s", COLOR_RESET);
        }
        printf("\n");
    }
}

int main()
{
    vec3 dim = {3,3,3}; // only NxNxN works
    Cube cube(dim);

    drawCube(cube);
    printf("\n");
    cube.Rotate(vec3(1, 0, 0));
    drawCube(cube);
    printf("\n");
    cube.Rotate(vec3(0, 1, 0));
    drawCube(cube);
    printf("\n");
    cube.Rotate(vec3(0, 0, 1));
    drawCube(cube);

    return 0;
}