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
    app_state->window = window_open("CWindow", 0, 0, 1280, 720);

    app_state->layer = malloc(sizeof(CLayer));
    memset(app_state->layer, 0, sizeof(CLayer));

    app_layer(app_state->layer);

    app_state->layer->startup();
}

void
app_shutdown(void)
{
    window_close(app_state->window);

    event_shutdown();
    input_shutdown();
    core_shutdown();

    app_state->layer->shutdown();
}

void
app_update(void)
{
    app_startup();

    while (app_state->is_running)
    {
        input_update();
        core_poll_event();

        app_state->layer->update(0.0f);

        core_sleep(1);
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
