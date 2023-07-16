#include <core/core.h>

API void
startup(void)
{
    log_info("Game: startup\n");
}

API void
update(f32 dt)
{
    local_variable b8 first_init = true;
    if (first_init)
    {
        first_init = false;
        log_info("Game: update\n");
    }

#if 0
    if (input_key_up(KeyCode_Q))
    {
        CEvent event = { 0 };
        event_fire(EventCode_AppQuit, event);
        log_info("Game: keycode: q\n");
    }

    if (input_button_down(MouseButton_Left))
    {
        log_info("Game: mouse.button: left (down)\n");
    }
    if (input_button_up(MouseButton_Left))
    {
        log_info("Game: mouse.button: left (up)\n");
    }
#endif
}

API void
shutdown(void)
{
    log_info("Game: shutdown\n");
}
