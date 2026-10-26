#pragma once
#include <math.h>
#include <stdbool.h>


typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

typedef struct Vector3D {
    float x;
    float y;
    float z;
} Vector3D;



/*****************************************************/
typedef struct Rect {
    float x, y, w, h;
} Rect;
