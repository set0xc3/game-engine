#include "engine/engine.h"

global_variable AppState *app_state;

void
app_startup(void)
{
    core_startup();
    event_startup();
    input_startup();

    event_register(EventCode_Everything, app_on_event);

    app_state = malloc(sizeof(AppState));
    memset(app_state, 0, sizeof(AppState));

    app_state->is_running = true;
    app_state->window = window_open("GameEngine", 0, 0, 1280, 720);

    app_state->layer = malloc(sizeof(CLayer));
    memset(app_state->layer, 0, sizeof(CLayer));

    app_layer(app_state->layer);

    app_state->layer->startup();
}

void
app_shutdown(void)
{
    app_state->layer->shutdown();
}

void
app_update(void)
{
    const f64 fps_max = 60.0;
    const f64 period_max = 1.0 / fps_max;
    const f64 perf_frequency = (f64)core_perf_frequency();

    f64 time = 0.0;
    f64 begin_counter = 0.0;
    f64 end_counter = 0.0;

    app_startup();

    while (app_state->is_running)
    {
        begin_counter = (f64)core_perf_counter();

        f64 counter_elapsed = (f64)(begin_counter - end_counter);
        f64 dt = (f64)(counter_elapsed / perf_frequency);
        f64 fps = (f64)(perf_frequency / counter_elapsed);

        if (dt >= period_max)
        {
            if (dt >= 1.0)
            {
                dt = period_max;
            }

            input_update();
            core_poll_event();

            app_state->layer->update(dt);

            end_counter = begin_counter;
            time += dt;

            log_info("%.3lf/fps, %.3lf/ms, %.3lf/t\n", fps, dt * 1000.0, time);
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
