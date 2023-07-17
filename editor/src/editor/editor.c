#include <core/core.h>

void
editor_startup(void)
{
    PROFILER_BEGIN(editor_startup);

    log_info("Editor: startup\n");

    PROFILER_END(editor_startup);
}

void
editor_update(f32 dt)
{
    // PROFILER_BEGIN(editor_update);

    local_variable b8 first_init = true;
    if (first_init)
    {
        first_init = false;
        log_info("Editor: update\n");
    }

#if 1
    if (input_key_up(KeyCode_Q))
    {
        debug_memory_handle();

        // CEvent event = { 0 };
        // event_fire(EventCode_AppQuit, event);
        // log_info("Editor: keycode: q\n");
    }

    if (input_button_down(MouseButton_Left))
    {
        log_info("Editor: mouse.button: left (down)\n");
    }
    if (input_button_up(MouseButton_Left))
    {
        log_info("Editor: mouse.button: left (up)\n");
    }
#endif

    // PROFILER_END(editor_update);
}

void
editor_shutdown(void)
{
    log_info("Editor: shutdown\n");
}

void
app_layer(CLayer *layer)
{
    layer->api.startup  = editor_startup;
    layer->api.update   = editor_update;
    layer->api.shutdown = editor_shutdown;
}
