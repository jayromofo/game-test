#pragma once

#include "SDL3/SDL.h"
#include "stdbool.h"

typedef struct LevelObject {
    int object_id;
    char *name;
    char *image_path;
    int x, y;
} LevelObject;

typedef struct Level {
    char* name;
    int level_id;
    int spawn;
} Level;

typedef struct LevelPackage {
    bool package_loaded;
    LevelObject level_objects[];
} LevelPack;
