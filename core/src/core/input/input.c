#include "core/core.h"

global_variable CInputState *input_state;

void
input_startup()
{
    input_state = malloc(sizeof(CInputState));
    memset(input_state, 0, sizeof(CInputState));
}

void
input_shutdown(void)
{
    free(input_state);
}

void
input_button_process(u32 button, b8 pressed)
{
    if (input_state->mouse_current.buttons[button] != pressed)
    {
        // log_info("button: %i, %i\n", button, pressed);

        input_state->mouse_current.buttons[button] = pressed;

        CEvent event = { 0 };
        event.data.u32[0] = button;
        event_fire(pressed ? EventCode_ButtonPressed
                           : EventCode_ButtonReleased,
                   event);
    }
}

void
input_key_process(u32 key, b8 pressed)
{
    if (input_state->keyboard_current.keys[key] != pressed)
    {
        log_info("key: %i, %i\n", key, pressed);

        input_state->keyboard_current.keys[key] = pressed;

        CEvent event = { 0 };
        event.data.u32[0] = key;
        event_fire(pressed ? EventCode_KeyPressed : EventCode_KeyReleased,
                   event);
    }
}

void
input_mouse_motion_process(i32 x, i32 y)
{
    if (input_state->mouse_current.x != x || input_state->mouse_current.y != y)
    {
        // log_info("mouse.position: (%i, %i)\n", x, y);

        input_state->mouse_current.x = x;
        input_state->mouse_current.y = y;

        CEvent event = { 0 };
        event.data.u32[0] = x;
        event.data.u32[1] = y;
        event_fire(EventCode_MouseMotion, event);
    }
}

void
input_mouse_scroll_process(i32 delta)
{
    if (input_state->mouse_current.wheel != delta)
    {
        // log_info("mouse.scroll: (%i)\n", delta);

        input_state->mouse_current.wheel = delta;

        CEvent event = { 0 };
        event.data.u32[0] = delta;
        event_fire(EventCode_MouseWheel, event);
    }
}

void
input_update(void)
{
    memcpy(input_state->keyboard_previous.keys,
           input_state->keyboard_current.keys, sizeof(CKeyboardState));

    memcpy(input_state->mouse_previous.buttons,
           input_state->mouse_current.buttons, sizeof(CMouseState));

    input_state->mouse_current.wheel = 0;
}

b8
input_button_pressed(u32 button)
{
    return input_state->mouse_previous.buttons[button]
           && input_state->mouse_current.buttons[button];
}

b8
input_button_down(u32 button)
{
    return !input_state->mouse_previous.buttons[button]
           && input_state->mouse_current.buttons[button];
}

b8
input_button_up(u32 button)
{
    return input_state->mouse_previous.buttons[button]
           && !input_state->mouse_current.buttons[button];
}

b8
input_key_pressed(u32 key)
{
    return input_state->keyboard_previous.keys[key]
           && input_state->keyboard_current.keys[key];
}

b8
input_key_down(u32 key)
{
    return !input_state->keyboard_previous.keys[key]
           && input_state->keyboard_current.keys[key];
}

b8
input_key_up(u32 key)
{
    return input_state->keyboard_previous.keys[key]
           && !input_state->keyboard_current.keys[key];
}

void
input_mouse_position_get(i32 *x, i32 *y)
{
    *x = input_state->mouse_current.x;
    *y = input_state->mouse_current.y;
}

void
input_mouse_wheel_get(i32 *delta)
{
    *delta = input_state->mouse_current.wheel;
}
