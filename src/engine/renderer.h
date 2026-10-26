#pragma once

#include <SDL3/SDL.h>
#include "util/mathx.h"

typedef struct Renderer Renderer;
typedef struct { Uint8 r, g, b, a; } Color;

Renderer* renderer_create(SDL_Window *window);
void renderer_destroy(Renderer* r);

void renderer_clear(Renderer* r, Color c);
void renderer_present(Renderer* r);


static inline SDL_FRect rect_to_SDL(Rect r){return  (SDL_FRect){r.x, r.y, r.w, r.h}; }
