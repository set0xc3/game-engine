#include "core/core.h"

#include "core/audio/audio.c"
#include "core/container/string8.c"
#include "core/container/vector2.c"
#include "core/container/vector3.c"
#include "core/container/vector4.c"
#include "core/debug/debug.c"
#include "core/event.c"
#include "core/input/input.c"
#include "core/library/library.c"
#include "core/logger/logger.c"
#include "core/math/math.c"
#include "core/memory/arena.c"
#include "core/window/window.c"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

void
core_startup(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        log_error("SDL could not initialize: %s\n", SDL_GetError());
    }
}

void
core_shutdown(void)
{
    SDL_Quit();
}

b8
core_poll_event(void)
{
    CEvent    send_event = { 0 };
    SDL_Event raw_event = { 0 };

    while (SDL_PollEvent(&raw_event))
    {
        switch (raw_event.type)
        {
        case SDL_QUIT:
            event_fire(EventCode_AppQuit, send_event);
            break;

        case SDL_WINDOWEVENT:
        {
            if (raw_event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                send_event.data.i32[0] = raw_event.window.data1;
                send_event.data.i32[1] = raw_event.window.data2;
                event_fire(EventCode_WindowResized, send_event);
            }
        }
        break;

        case SDL_MOUSEMOTION:
            input_mouse_motion_process(raw_event.motion.x, raw_event.motion.y);
            break;

        case SDL_MOUSEWHEEL:
            input_mouse_scroll_process(raw_event.wheel.y);
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            CMouseButton button = MouseButton_Count;
            b8 pressed = raw_event.button.state == SDL_PRESSED ? true : false;

            switch (raw_event.button.button)
            {
            case SDL_BUTTON_LEFT:
                button = MouseButton_Left;
                break;
            case SDL_BUTTON_MIDDLE:
                button = MouseButton_Middle;
                break;
            case SDL_BUTTON_RIGHT:
                button = MouseButton_Right;
                break;
            }

            if (button != MouseButton_Count)
            {
                input_button_process(button, pressed);
            }
        }
        break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            CKeyCode key = KeyCode_Count;
            b8 pressed = raw_event.key.state == SDL_PRESSED ? true : false;

            switch (raw_event.key.keysym.sym)
            {
            case SDLK_w:
                key = KeyCode_W;
                break;
            case SDLK_s:
                key = KeyCode_S;
                break;
            case SDLK_a:
                key = KeyCode_A;
                break;
            case SDLK_d:
                key = KeyCode_D;
                break;
            case SDLK_q:
                key = KeyCode_Q;
                break;
            case SDLK_e:
                key = KeyCode_E;
                break;
            case SDLK_ESCAPE:
                key = KeyCode_Escape;
                break;
            }

            if (key != KeyCode_Count)
            {
                input_key_process(key, pressed);
            }
        }
        break;
        }
    }

    return true;
}

void
core_sleep(u32 ms)
{
    SDL_Delay(ms);
}

u64
core_perf_counter(void)
{
    return SDL_GetPerformanceCounter();
}

u64
core_perf_frequency(void)
{
    return SDL_GetPerformanceFrequency();
}
