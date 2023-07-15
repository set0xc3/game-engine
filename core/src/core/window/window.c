#include "core/core.h"

#include <SDL2/SDL.h>

#include "core/window/window_internal.c"

CWindow *
window_open(const char *title, i32 xpos, i32 ypos, i32 width, i32 height)
{
    CWindow *result = calloc(sizeof(CWindow), 1);
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
window_close(CWindow *window)
{
    SDL_DestroyWindow(window->handle);
    free(window);
}
