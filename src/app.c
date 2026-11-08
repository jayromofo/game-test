#include "app.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>

SDL_AppResult app_interate(Context *ctx){

    Uint64 now = SDL_GetTicks();
    ctx->last_ticks = now;

    return SDL_APP_CONTINUE;
}

void app_shutdown(Context *ctx){
    SDL_free(ctx->assets);
}
