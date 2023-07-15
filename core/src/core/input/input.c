#include "core/core.h"

global_variable InputState *this;

void
input_startup()
{
    if (this != NULL)
    {
        return;
    }

    this = calloc(sizeof(InputState), 1);
}

void
input_shutdown(void)
{
    free(this);
}

void
input_button_process(MouseButton button, b8 state)
{
    this->mouse_current.buttons[button] = state;

    EventCtx ctx = { 0 };
    ctx.data.u16[0] = button;
    event_fire(state ? EventCode_ButtonPressed : EventCode_ButtonReleased, 0,
               ctx);
}

void
input_key_process(KeyCode key, b8 state)
{
    this->keyboard_current.keys[key] = state;

    EventCtx ctx = { 0 };
    ctx.data.u16[0] = key;
    event_fire(state ? EventCode_KeyPressed : EventCode_KeyReleased, 0, ctx);
}

void
input_mouse_motion_process(i16 x, i16 y)
{
    this->mouse_current.x = x;
    this->mouse_current.y = y;

    EventCtx ctx = { 0 };
    ctx.data.u16[0] = x;
    ctx.data.u16[1] = y;
    event_fire(EventCode_MouseMotion, 0, ctx);
}

void
input_mouse_scroll_process(i16 z_delta)
{
    this->mouse_current.wheel = z_delta;

    EventCtx ctx = { 0 };
    ctx.data.u16[0] = z_delta;
    event_fire(EventCode_MouseWheel, 0, ctx);
}

void
input_update(void)
{
    memcpy(this->keyboard_previous.keys, this->keyboard_current.keys,
           sizeof(KeyboardState));
    memcpy(this->mouse_previous.buttons, this->mouse_current.buttons,
           sizeof(MouseState));

    this->mouse_current.wheel = 0;
}

b32
input_button_pressed(i16 button)
{
    return this->mouse_previous.buttons[button]
           && this->mouse_current.buttons[button];
}

b32
input_button_down(i16 button)
{
    return !this->mouse_previous.buttons[button]
           && this->mouse_current.buttons[button];
}

b32
input_button_up(i16 button)
{
    return this->mouse_previous.buttons[button]
           && !this->mouse_current.buttons[button];
}

b32
input_key_pressed(i16 key)
{
    return this->keyboard_previous.keys[key]
           && this->keyboard_current.keys[key];
}

b32
input_key_down(i16 key)
{
    return !this->keyboard_previous.keys[key]
           && this->keyboard_current.keys[key];
}

b32
input_key_up(i16 key)
{
    return this->keyboard_previous.keys[key]
           && !this->keyboard_current.keys[key];
}

void
input_mouse_position_get(i16 *x, i16 *y)
{
    *x = this->mouse_current.x;
    *y = this->mouse_current.y;
}

void
input_mouse_wheel_get(i16 *z_delta)
{
    *z_delta = this->mouse_current.wheel;
}
