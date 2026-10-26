#include "engine/input.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <string.h>


void input_init(Input *in){

    memset(in, 0, sizeof *in);
    in->keymap[SDL_SCANCODE_ESCAPE] = ACTION_MENU;
    in->keymap[SDL_SCANCODE_Q] = ACTION_QUIT;
    in->keymap[SDL_SCANCODE_R] = ACTION_RELOAD;
    in->keymap[SDL_SCANCODE_W] = ACTION_FORWARD;
    in->keymap[SDL_SCANCODE_A] = ACTION_LEFT;
    in->keymap[SDL_SCANCODE_S] = ACTION_BACK;
    in->keymap[SDL_SCANCODE_D] = ACTION_RIGHT;
    in->keymap[SDL_SCANCODE_M] = ACTION_MAP;
    in->keymap[SDL_SCANCODE_SPACE] = ACTION_JUMP;
    in->keymap[SDL_SCANCODE_F5] = ACTION_QUICK_SAVE;
    in->keymap[SDL_SCANCODE_F8] = ACTION_QUICK_LOAD;
}

void input_handle_event(Input *in, const SDL_Event *e){

    switch(e->type){
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP: {
            if (e->key.repeat) return;
            if (e->key.scancode >= SDL_SCANCODE_COUNT) return;

            Action a = in->keymap[e->key.scancode];
            if (a == ACTION_NONE) return;

            if (e->key.down) {
                if (!in->held[a]) in->pressed[a] = true;
                in->held[a] = true;
            } else {
                in->held[a] = false;
                in->released[a] = true;
            }
            break;
        }
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            memset(in->held,0,sizeof in->held);
            break;
        default:
            break;
    }
}

void input_end_frame(Input *in){
    memset(in->pressed, 0, sizeof *in->pressed);
    memset(in->released, 0, sizeof *in->released);
}

/*
void controller_map(){

    if(e->type == SDL_EVENT_GAMEPAD_ADDED){
        const SDL_JoystickID which = e->gdevice.which;
        SDL_Gamepad *gamepad = SDL_OpenGamepad(which);
    } else if(e->type == SDL_EVENT_GAMEPAD_REMOVED){
        const SDL_JoystickID which = e->gdevice.which;
        SDL_Gamepad *gamepad = SDL_GetGamepadFromID(which);
        if (gamepad) {
            SDL_CloseGamepad(gamepad);
        }
    } else if(e->type == SDL_EVENT_GAMEPAD_AXIS_MOTION){
        printf("Axis Moved: \n");
        printf("%s\n", SDL_GetGamepadStringForAxis((SDL_GamepadAxis)e->gaxis.axis));
        printf("| Value: %u \n", e->gaxis.value);
    } else if (e->type == SDL_EVENT_JOYSTICK_BATTERY_UPDATED){

    } else if((e->type == SDL_EVENT_GAMEPAD_BUTTON_UP) || (e->type == SDL_EVENT_GAMEPAD_BUTTON_DOWN)){

    } else if (e->type == SDL_EVENT_KEY_DOWN){
        // handle_key_e -- May need to switch to use context
        Action action = handle_key_event(e);
        if (action == ACTION_FORWARD){
            SDL_Log("Action Forward");
        } else if (action == ACTION_BACK){
            SDL_Log("Action Back");
        } else if (action == ACTION_RELOAD){
            SDL_Log("Action Reload");
        } else if (action == ACTION_QUIT){
            SDL_Log("Action Quit");
        } else if (action == ACTION_USEITEM){
            SDL_Log("Action Use Item");
        } else if (action == ACTION_LEFT){
            SDL_Log("Action Left");
        } else if (action == ACTION_RIGHT){
            SDL_Log("Action Right");
        }
    }

}
*/
