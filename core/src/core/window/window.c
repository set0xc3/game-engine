#include "core/core.h"

#include <SDL2/SDL.h>

#include "core/window/window_internal.c"

WindowState *
window_open(const char *title, i32 xpos, i32 ypos, i32 width, i32 height)
{
    WindowState *result = calloc(sizeof(WindowState), 1);
    result->title = title;
    result->rect.x = xpos;
    result->rect.y = ypos;
    result->rect.width = width;
    result->rect.height = height;

    u32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    result->handle = SDL_CreateWindow(result->title, result->rect.x,
                                      result->rect.y, result->rect.width,
                                      result->rect.height, window_flags);
    if (!result->handle)
    {
        log_error("[SDL] Failed create window\n");
        return NULL;
    }

    result->renderer = SDL_CreateRenderer(result->handle, -1,
                                          SDL_RENDERER_ACCELERATED
                                              | SDL_RENDERER_TARGETTEXTURE);
    if (!result->renderer)
    {
        log_error("[SDL] Failed create renderer\n");
        return NULL;
    }

    result->texture = SDL_CreateTexture(
        result->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        result->rect.width, result->rect.height);

    return result;
}

void
window_close(WindowState *window)
{
    SDL_DestroyWindow(window->handle);
    free(window);
}

#if 0
b32
window_event_poll(WindowEvent *return_event)
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        if (event.type == SDL_WINDOWEVENT)
        {
            switch (event.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                return_event->kind = EventCode_AppQuit;
            }
        }

        switch (event.type)
        {
        case SDL_QUIT:
            return_event->kind = EventCode_AppQuit;
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                return_event->kind = EventCode_WindowResized;
                return_event->width = event.window.data1;
                return_event->height = event.window.data2;
            }
            break;
        case SDL_MOUSEMOTION:
            return_event->kind = EventCode_MouseMotion;
            return_event->x = event.motion.x;
            return_event->y = event.motion.y;
            break;
        case SDL_MOUSEWHEEL:
            return_event->kind = EventCode_MouseWheel;
            return_event->xwheel = event.wheel.x;
            return_event->ywheel = event.wheel.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            return_event->kind = SDL_PRESSED ? EventCode_ButtonPressed
                                             : EventCode_ButtonReleased;
            switch (event.button.button)
            {
            case SDL_BUTTON_LEFT:
                return_event->code = MouseButton_Left;
                break;
            case SDL_BUTTON_MIDDLE:
                return_event->code = MouseButton_Middle;
                break;
            case SDL_BUTTON_RIGHT:
                return_event->code = MouseButton_Right;
                break;
            }
        }
        break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            return_event->kind
                = SDL_PRESSED ? EventCode_KeyPressed : EventCode_KeyReleased;
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                return_event->code = KeyCode_W;
                break;
            case SDLK_s:
                return_event->code = KeyCode_S;
                break;
            case SDLK_a:
                return_event->code = KeyCode_A;
                break;
            case SDLK_d:
                return_event->code = KeyCode_D;
                break;
            case SDLK_q:
                return_event->code = KeyCode_Q;
                break;
            case SDLK_e:
                return_event->code = KeyCode_E;
                break;
            case SDLK_ESCAPE:
                return_event->code = KeyCode_Escape;
                break;
            }
        }
        break;
        }

        return true;
    }

    return false;
    return false;
}
#endif
