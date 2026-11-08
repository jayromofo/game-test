#pragma once
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct Assets {
    char* asset_path;

} Assets;

bool assets_create();
bool assets_add_to_list();
