#include "raylib.h"
#include "../engine/headers/generics.h"

#define MAX_OBJ 200

dWorldID world;
dJointGroupID contactGroup;

void setTransform(const float pos[3], const float R[12], Matrix* matrix)
{
    matrix->m0 = R[0];
    matrix->m1 = R[4];
    matrix->m2 = R[8];

    matrix->m4 = R[1];
    matrix->m5 = R[5];
    matrix->m6 = R[9];

    matrix->m8 = R[2];
    matrix->m9 = R[6];
    matrix->m10 = R[10];

    matrix->m11 = pos[0];
    matrix->m12 = pos[1];
    matrix->m13 = pos[2];
}
