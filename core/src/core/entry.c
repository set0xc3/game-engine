#include "core/core.h"

#include "core/internal.h"

global_variable b8 is_running = true;

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
    debug_startup();
    core_startup();

    core_state->layer.api.startup  = module_startup_stub;
    core_state->layer.api.update   = module_update_stub;
    core_state->layer.api.shutdown = module_shutdown_stub;
    layer_main(&core_state->layer);
    core_state->layer.api.startup();

    CLibrary *library     = library_load("./libgame");
    library->api.startup  = module_startup_stub;
    library->api.update   = module_update_stub;
    library->api.shutdown = module_shutdown_stub;

    library->api.startup  = library_load_function(library, "startup");
    library->api.update   = library_load_function(library, "update");
    library->api.shutdown = library_load_function(library, "shutdown");
    core_state->game      = library;
    core_state->game->api.startup();

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
            core_state->game->api.update(dt);

            end_counter = begin_counter;
            time += dt;

            // log_info("%.3lf/fps, %.3lf/ms, %.3lf/t\n", fps, dt * 1000.0,
            // time);
        }

        core_sleep((u64)period_max);
    }

    core_state->game->api.shutdown();
    core_state->layer.api.shutdown();
    core_shutdown();
    debug_shutdown();

    return 0;
}
