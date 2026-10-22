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


typedef enum {
    ACTION_NONE,
    ACTION_RELOAD,
    ACTION_JUMP,
    ACTION_MAP,
    ACTION_FORWARD,
    ACTION_BACK,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_QUIT,
    ACTION_USEITEM,
    ACTION_MENU
} Action;


typedef struct EventMessage{
    char *str;
    SDL_Color color;
    Uint64 start_ticks;
    struct EventMessage *next;
} EventMessage;

typedef struct {

} GameContext;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *render;
    GameContext *ctx;
} AppState;

static EventMessage messages;
static EventMessage *messages_tail = &messages;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

Action handle_key_event(const SDL_Event *e);


SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    SDL_SetAppMetadata("Test Program", "1.0", "com.example.test-program");

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

    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    } else if(event->type == SDL_EVENT_GAMEPAD_ADDED){
        const SDL_JoystickID which = event->gdevice.which;
        SDL_Gamepad *gamepad = SDL_OpenGamepad(which);
    } else if(event->type == SDL_EVENT_GAMEPAD_REMOVED){
        const SDL_JoystickID which = event->gdevice.which;
        SDL_Gamepad *gamepad = SDL_GetGamepadFromID(which);
        if (gamepad) {
            SDL_CloseGamepad(gamepad);
        }
    } else if(event->type == SDL_EVENT_GAMEPAD_AXIS_MOTION){
        printf("Axis Moved: \n");
        printf("%s\n", SDL_GetGamepadStringForAxis((SDL_GamepadAxis)event->gaxis.axis));
        printf("| Value: %u \n", event->gaxis.value);
    } else if (event->type == SDL_EVENT_JOYSTICK_BATTERY_UPDATED){

    } else if((event->type == SDL_EVENT_GAMEPAD_BUTTON_UP) || (event->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN)){

    } else if (event->type == SDL_EVENT_KEY_DOWN){
        // handle_key_event -- May need to switch to use context
        Action action = handle_key_event(event);
        if (action == ACTION_FORWARD){
            SDL_Log("Action Forward");
        } else if (action == ACTION_BACK){
            SDL_Log("Action Back");
        } else if (action == ACTION_RELOAD){
            SDL_Log("Action Reload");
        } else if (action == ACTION_QUIT){
            SDL_Log("Action Quit");
            return SDL_APP_FAILURE;
        } else if (action == ACTION_USEITEM){
            SDL_Log("Action Use Item");
        } else if (action == ACTION_LEFT){
            SDL_Log("Action Left");
        } else if (action == ACTION_RIGHT){
            SDL_Log("Action Right");
        }

    }
    return SDL_APP_CONTINUE;
}

Action handle_key_event(const SDL_Event *e){
    SDL_Log("Scancode: %d", e->key.scancode);

    if (e->type != SDL_EVENT_KEY_DOWN || e->key.repeat)
        return ACTION_NONE;

    switch(e->key.scancode){
        case SDL_SCANCODE_ESCAPE: {
            SDL_Log("ESC for Menu");
            return ACTION_MENU;
        };
        case SDL_SCANCODE_Q: {
            SDL_Log("Q for Quit");
            return ACTION_QUIT;
        };
        case SDL_SCANCODE_R: {
            SDL_Log("A for reload");
            return ACTION_RELOAD;
        };
        case SDL_SCANCODE_W: {
            SDL_Log("A for walk forward");
            return ACTION_FORWARD;
        };
        case SDL_SCANCODE_D: {
            SDL_Log("A for move right");
            return ACTION_RIGHT;
        };
        case SDL_SCANCODE_A: {
            SDL_Log("A for move left");
            return ACTION_LEFT;
        };
        case SDL_SCANCODE_S: {
            SDL_Log("D for Down");
            return ACTION_BACK;
        };
        case SDL_SCANCODE_M: {
            SDL_Log("M for MAP");
            return ACTION_MAP;
        };
        default: {
            SDL_Log("Default");
            return ACTION_NONE;
        };
    }
}

SDL_AppResult SDL_AppIterate(void *appstate){

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

    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    // SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    static const SDL_FPoint line_points[] = {
        { 100, 354 }, { 220, 230 }, { 140, 230 }, { 320, 100 }, { 500, 230 },
        { 420, 230 }, { 540, 354 }, { 400, 354 }, { 100, 354 }
    };

    SDL_SetRenderDrawColor(renderer, 100,100,100,SDL_ALPHA_OPAQUE);

    // Clear the window to draw color
    SDL_RenderClear(renderer);

    /****v Code Here v****/
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
    /****^ Code Here ^****/

    // Put the newly-cleared rendering on the screen
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}


void SDL_AppQuit(void *appstate, SDL_AppResult result){
    SDL_Quit();
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
