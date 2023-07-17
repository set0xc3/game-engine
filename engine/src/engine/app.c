#include "engine/app.h"

global_variable AppState *app_state;

#ifdef LAYER_TARGET_NONE
void
app_layer(CLayer *layer)
{
}
#endif

void
app_startup(void)
{
    app_state = MemoryAllocStruct(AppState);
    MemoryZeroStruct(app_state, AppState);
    app_state->is_running = true;

    core_startup();

    event_register(EventCode_Everything, app_on_event);

    app_state->layer = MemoryAllocStruct(CLayer);
    MemoryZeroStruct(app_state->layer, CLayer);

    app_state->layer->api.startup  = module_startup_stub;
    app_state->layer->api.update   = module_update_stub;
    app_state->layer->api.shutdown = module_shutdown_stub;
    app_layer(app_state->layer);

    CLibrary *library     = library_load("./libgame");
    library->api.startup  = module_startup_stub;
    library->api.update   = module_update_stub;
    library->api.shutdown = module_shutdown_stub;

    library->api.startup  = library_load_function(library, "startup");
    library->api.update   = library_load_function(library, "update");
    library->api.shutdown = library_load_function(library, "shutdown");
    app_state->game       = library;

    app_state->layer->api.startup();
    app_state->game->api.startup();
}

void
app_shutdown(void)
{
    app_state->layer->api.shutdown();
    app_state->game->api.shutdown();

    library_unload(app_state->game);

    core_shutdown();

    MemoryFree(app_state->layer);
    MemoryFree(app_state);
}

void
app_update(void)
{
    app_startup();

    const f64 fps_max        = 60.0;
    const f64 period_max     = 1.0 / fps_max;
    const f64 perf_frequency = (f64)core_perf_frequency();

    f64 time          = 0.0;
    f64 begin_counter = 0.0;
    f64 end_counter   = 0.0;

    while (app_state->is_running)
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

            app_state->layer->api.update(dt);
            app_state->game->api.update(dt);

            end_counter = begin_counter;
            time += dt;

            // log_info("%.3lf/fps, %.3lf/ms, %.3lf/t\n", fps, dt * 1000.0,
            // time);
        }

        core_sleep((u64)period_max);
    }

    app_shutdown();
}

b8
app_on_event(u32 code, CEvent event)
{
    switch (code)
    {
    case EventCode_AppQuit:
    {
        app_state->is_running = false;
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
            app_state->is_running = false;
        }
    }
    break;
    }

    return true;
}
