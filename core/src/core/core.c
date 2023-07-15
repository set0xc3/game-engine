#include "core/core.h"

#include "core/audio/audio.c"
#include "core/container/string8.c"
#include "core/container/vector2.c"
#include "core/container/vector3.c"
#include "core/container/vector4.c"
#include "core/debug/debug.c"
#include "core/event.c"
#include "core/logger/logger.c"
#include "core/math/math.c"
#include "core/memory/arena.c"
#include "core/window/window.c"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

void
core_startup(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        log_error("SDL could not initialize: %s\n", SDL_GetError());
    }
}

void
core_shutdown(void)
{
    SDL_Quit();
}

void
core_sleep(u32 ms)
{
    SDL_Delay(ms);
}

u64
core_perf_counter(void)
{
    return SDL_GetPerformanceCounter();
}

u64
core_perf_frequency(void)
{
    return SDL_GetPerformanceFrequency();
}
