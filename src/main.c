#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>

#include "app.h"


typedef struct EventMessage{
    char *str;
    SDL_Color color;
    Uint64 start_ticks;
    struct EventMessage *next;
} EventMessage;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *render;
    Context *ctx;
} AppState;

static EventMessage messages;
static EventMessage *messages_tail = &messages;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

Action handle_key_event(const SDL_Event *e);


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    SDL_SetAppMetadata("Test Program", "1.0", "com.example.test-program");

    Context *ctx = SDL_calloc(1, sizeof(Context));
    if (!ctx) return SDL_APP_FAILURE;
    *appstate = ctx;

    // if (!app_init(ctx)) return SDL_APP_FAILURE;

    if (!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("game/test/program", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)){
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    Context *ctx = appstate;
    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }
    input_handle_event(&ctx->input, event);
    return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void *appstate){

    Context *ctx = appstate;
    return app_interate(ctx);

    // return ctx->running ? SDL_APP_CONTINUE : SDL_APP_SUCCESS;

    /*
    SDL_Surface *surface = NULL;
    char *png_path = NULL;
    const Uint64 now = SDL_GetTicks();
    const float msg_lifetime = 3500.0f;
    EventMessage *msg = messages.next;

    int winx = 640, winy = 480;

    SDL_GetWindowSize(window, &winx, &winy);

    while(msg){
        if (true){
            SDL_free(msg->str);
            SDL_free(msg);
            msg = messages.next;
            continue;
        } // fix
    }
    */

    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    // const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    // const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    // const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    // SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /*
    static const SDL_FPoint line_points[] = {
        { 100, 354 }, { 220, 230 }, { 140, 230 }, { 320, 100 }, { 500, 230 },
        { 420, 230 }, { 540, 354 }, { 400, 354 }, { 100, 354 }
    };

    SDL_SetRenderDrawColor(renderer, 100,100,100,SDL_ALPHA_OPAQUE);

    // Clear the window to draw color
    SDL_RenderClear(renderer);
    */

    /****v Code Here v****/
    /*
    SDL_FRect dst_rect;

    const float direction = ((now % 2000) >= 1000) ? 1.0f : -1.0f;
    const float scale = ((float) (((int) (now % 1000)) - 500) / 500.0f) * direction;

    SDL_RenderTexture(renderer, texture, NULL, &dst_rect);

    SDL_FRect filledRect = {150.0f, 150.0f, 200.0f, 200.0f};
    SDL_FRect outlineRect = {450.0f, 150.0f, 200.0f, 200.0f};

    SDL_SetRenderDrawColor(renderer, 20,30,50,255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    SDL_RenderFillRect(renderer, &filledRect);

    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    SDL_RenderFillRect(renderer, &outlineRect);
    */
    /****^ Code Here ^****/

    // Put the newly-cleared rendering on the screen
    // SDL_RenderPresent(renderer);

    // return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
    Context *ctx = appstate;
    if (!ctx) return;
    app_shutdown(ctx);
    SDL_free(ctx);
}


/**************************************************************/
/****  Clean Up  **********************************************/
/**************************************************************/
static inline void cleanup_renderer(SDL_Renderer *r){ if (r) SDL_DestroyRenderer(r); }
static inline void cleanup_window(SDL_Window *win){if (win) SDL_DestroyWindow(win); }
static inline void cleanup_texture(SDL_Texture *tex){ if (tex) SDL_DestroyTexture(tex); }
static inline void cleanup_surface(SDL_Surface *surf){ if (surf) SDL_DestroySurface(surf); }
#define cleanup(p) _Generic((p)),       \
    SDL_Renderer *: cleanup_renderer,   \
    SDL_Window *: cleanup_window,       \
    SDL_Texture *: cleanup_texture,     \
    SDL_Surface *: cleanup_surface      \
)(p)
/***********************************************************************/
