#include "core/core.h"

#include "core/internal.h"

#include <SDL2/SDL.h>

global_variable b8          is_running = true;
global_variable CCoreState *core_state;

internal b8
core_on_event(u32 code, CEvent event)
{
    switch (code)
    {
    case EventCode_AppQuit:
    {
        is_running = false;
    }
    break;
    case EventCode_KeyPressed:
    {
    }
    break;
    case EventCode_KeyReleased:
    {
        CKeyCode key = event.data.u32[0];
        if (key == KeyCode_Escape)
        {
            is_running = false;
        }
    }
    break;
    }

    return true;
}

int
main(int argc, char *argv[])
{
    core_state = MemoryAllocStruct(CCoreState);
    MemoryZeroStruct(core_state, CCoreState);

    debug_startup();
    core_startup();
    event_startup();
    input_startup();
    scene_startup();

    // NOTE: Load layer and checking
    core_state->layer.api.startup  = module_startup_stub;
    core_state->layer.api.update   = module_update_stub;
    core_state->layer.api.shutdown = module_shutdown_stub;
    // layer_main(&core_state->layer);
    if (core_state->layer.is_valid)
    {
        if (core_state->layer.api.startup == NULL
            || core_state->layer.api.update == NULL
            || core_state->layer.api.shutdown == NULL)
        {
            core_state->layer.is_valid     = false;
            core_state->layer.api.startup  = module_startup_stub;
            core_state->layer.api.update   = module_update_stub;
            core_state->layer.api.shutdown = module_shutdown_stub;
        }
    }

    // NOTE: Load game library and checking
    core_state->game_dll.api.startup  = module_startup_stub;
    core_state->game_dll.api.update   = module_update_stub;
    core_state->game_dll.api.shutdown = module_shutdown_stub;
    // core_state->game_dll              = library_load("./libgame");
    if (core_state->game_dll.is_valid)
    {
        core_state->game_dll.api.startup
            = library_load_function(&core_state->game_dll, "startup");
        core_state->game_dll.api.update
            = library_load_function(&core_state->game_dll, "update");
        core_state->game_dll.api.shutdown
            = library_load_function(&core_state->game_dll, "shutdown");

        if (core_state->game_dll.api.startup == NULL
            || core_state->game_dll.api.update == NULL
            || core_state->game_dll.api.shutdown == NULL)
        {
            core_state->game_dll.is_valid     = false;
            core_state->game_dll.api.startup  = module_startup_stub;
            core_state->game_dll.api.update   = module_update_stub;
            core_state->game_dll.api.shutdown = module_shutdown_stub;
        }
    }

    core_state->layer.api.startup();
    core_state->game_dll.api.startup();

    core_state->window = window_open("GameEngine", 0, 0, 1280, 720);
    event_register(EventCode_Everything, core_on_event);

    const f64 fps_max        = 60.0;
    const f64 period_max     = 1.0 / fps_max;
    const f64 perf_frequency = (f64)core_perf_frequency();

    f64 time          = 0.0;
    f64 begin_counter = 0.0;
    f64 end_counter   = 0.0;

    while (is_running)
    {
        begin_counter = (f64)core_perf_counter();

        f64 counter_elapsed = (f64)(begin_counter - end_counter);
        f64 dt              = (f64)(counter_elapsed / perf_frequency);
        f64 fps             = (f64)(perf_frequency / counter_elapsed);

        if (dt >= period_max)
        {
            if (dt >= 1.0)
            {
                dt = period_max;
            }

            core_update();
            core_state->layer.api.update(dt);
            core_state->game_dll.api.update(dt);

            end_counter = begin_counter;
            time += dt;

            // log_info("%.3lf/fps, %.3lf/ms, %.3lf/t\n", fps, dt * 1000.0,
            // time);
        }

        core_sleep((u64)period_max);
    }

    window_close(core_state->window);
    core_state->game_dll.api.shutdown();
    core_state->layer.api.shutdown();
    event_shutdown();
    input_shutdown();
    scene_shutdown();
    core_shutdown();
    debug_shutdown();

    return 0;
}
