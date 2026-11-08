#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <stdbool.h>
#include <game/actions.h>

typedef enum {
    ACTION_NONE,
    ACTION_RELOAD,
    ACTION_JUMP,
    ACTION_FORWARD,
    ACTION_BACK,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_USEITEM,


    ACTION_QUIT,
    ACTION_MENU,
    ACTION_MAP,
    ACTION_QUICK_LOAD,
    ACTION_QUICK_SAVE,

    ACTION_COUNT  // Keeps count of the Actions
} Action;

typedef struct Input {
    bool held[ACTION_COUNT];
    bool pressed[ACTION_COUNT];
    bool released[ACTION_COUNT];
    Action keymap[SDL_SCANCODE_COUNT];
} Input;

void input_init(Input *in);
void input_handle_event(Input *in, const SDL_Event *e);
void input_end_frame(Input *in);

static inline bool input_held(const Input *in, Action a)        {return in->held[a];}
static inline bool input_pressed(const Input *in, Action a)     {return in->pressed[a];}
static inline bool static_released(const Input *in, Action a)   {return in->released[a];}
