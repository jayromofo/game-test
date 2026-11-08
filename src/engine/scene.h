#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Scene Scene;
typedef struct Context Context;

struct Scene {
    void (*on_enter) (Scene *scene, Context *ctx);
    void (*on_exit) (Scene *scene, Context *ctx);
    void (*on_pause) (Scene *scene, Context *ctx);
    void (*on_resume) (Scene *scene, Context *ctx);
    void (*handle_event) (Scene *scene, Context *ctx, SDL_Event *e);
    void (*update) (Scene *scene, Context *ctx);
    void (*render) (Scene *scene, Context *ctx);
    void (*destroy) (Scene *scene, Context *ctx);
    bool transparent;
};

#define SCENE_STACK_MAX 8
#define SCENE_PENDING_MAX 8

typedef enum { SCENE_OP_PUSH, SCENE_OP_POP, SCENE_OP_REPLACE} SceneOpKind;

typedef struct SceneOp {
    SceneOpKind kind;
    Scene *scene;
} SceneOp;

typedef struct SceneManager {
    Scene *stack[SCENE_STACK_MAX];
    int count;
    SceneOp pending[SCENE_PENDING_MAX];
    int pending_count;
} SceneManager;

void scene_manager_init(SceneManager *m);
void scene_manager_clear(SceneManager *m, Context *ctx);

void scene_manager_push(SceneManager *m, Context *ctx);
void scene_manager_pop(SceneManager *m, Context *ctx);
void scene_manager_replace(SceneManager *m, Context *ctx);
void scene_manager_apply_pending(SceneManager *m, Context *ctx);

void scene_manager_handle_event(SceneManager *m, Context *ctx, SDL_Event *e);
void scene_manager_update(SceneManager *m, Context *ctx);
void scene_manager_render(SceneManager *m, Context *ctx);

bool scene_manager_empty(const SceneManager *m);
Scene *scene_manager_top(const SceneManager *m);
