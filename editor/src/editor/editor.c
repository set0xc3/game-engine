#include <engine/engine.h>

void
editor_startup(void)
{
    log_info("  startup\n");
}

void
editor_update(f32 dt)
{
    local_variable b8 first_init = true;
    if (first_init)
    {
        first_init = false;
        log_info("  update\n");
    }

    if (input_key_up(KeyCode_Q))
    {
        CEvent event = { 0 };
        event_fire(EventCode_AppQuit, event);
        log_info("  keycode: q\n");
    }

    if (input_button_down(MouseButton_Left))
    {
        log_info("  mouse.button: left (down)\n");
    }
    if (input_button_up(MouseButton_Left))
    {
        log_info("  mouse.button: left (up)\n");
    }
}

void
editor_shutdown(void)
{
    log_info("  shutdown\n");
}

void
app_layer(CLayer *layer)
{
    log_info("Layer: editor\n");

    layer->startup = editor_startup;
    layer->update = editor_update;
    layer->shutdown = editor_shutdown;
}
