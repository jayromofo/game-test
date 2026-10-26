#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include "engine/assets.h"
#include "engine/audio.h"
#include "engine/input.h"
#include "engine/scene.h"

#define WINDOW_W    1280
#define WINDOW_H    720
#define FIXED_DT    (1.0f / 60.0f)
#define MAX_FRAME   0.25;

typedef struct Context {
    SDL_Window              *window;
    SDL_Renderer            *renderer;
    Assets                  *assets;
    Audio                   *audio;
    SceneManager            scenes;
    Input                   input;

    const char              *base_path;  /* owned by SDL, do not free */
    Uint64                  last_ticks;
    float                   accumulator;
    float                   dt;
    bool                    running;
} Context;

bool app_init(Context *ctx);
SDL_AppResult app_event(Context *ctx, const SDL_Event *e);
SDL_AppResult app_interate(Context *ctx);
void app_shutdown(Context *ctx);
