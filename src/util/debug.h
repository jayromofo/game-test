#pragma once
#include <SDL3/SDL_log.h>
#include <stdbool.h>

#define TODO() SDL_Log("TODO: %s", __func__);  // Use in .c files, not .h
#define TODO_ONCE() do { static bool done; if (!done) {done = true; TODO();}} while(0)
