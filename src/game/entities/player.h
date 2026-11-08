#pragma once
#include "util/mathx.h"

typedef struct Context context;

typedef struct Player {
    Vec2 pos;
    Vec2 vel;
    int health;
} Player;
void player_update(Player *p, const Context *ctx);
