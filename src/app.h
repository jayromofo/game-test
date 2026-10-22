#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "engine/assets.h"
#include "engine/audio.h"
#include "engine/input.h"

typedef struct Context {
    SDL_Window  *window;
    SDL_Renderer *renderer;
    Assets *assets;
    Audio *audio;
    Input input;
    float dt;
    bool running;
} Context;

bool app_init(Context *ctx);
void app_shutdown(Context *ctx);
