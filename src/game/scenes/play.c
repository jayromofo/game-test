#include "game/scenes/play.h"

#include <SDL3/SDL.h>

#include "app.h"
#include <SDL3/SDL_stdinc.h>
#include <engine/scene.h>
#include <engine/input.h>
#include <game/level.h>
#include <game/entities/player.h>



typedef struct PlayScene {
    Scene base;
    Player player;
    Level level;
    int score;
    int level_id;
} PlayScene;

static void play_enter(Scene *scene, Context *ctx){

}

static void play_update(Scene *scene, Context *ctx){

}

static void play_render(Scene *scene, Context *ctx){

}

static void play_update(Scene *self, Context *ctx){
    PlayScene *s = (PlayScene *)self;
    player_update(&s->player, ctx);
}

static *play_scene_create(int level_id){
    PlayScene *s = SDL_calloc(1, sizeof *s);
    s->base = (Scene){
        .on_enter = play_enter,
        .update = play_update,
        .render = play_render,
        .destroy = SDL_free,
    };
    return &s->base;
}
