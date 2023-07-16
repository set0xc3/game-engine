#include "core/core.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core/asset/asset_internal.c"
#include "core/graphics/window_internal.c"

void
asset_init(void)
{
    i32 img_flags = IMG_INIT_PNG;
    if ((IMG_Init(img_flags) & img_flags) != img_flags)
    {
        log_error("Failed to initialize SDL_image: %s\n", IMG_GetError());
    }
}

void
asset_destroy(void)
{
    IMG_Quit();
}

void *
asset_file_rw_data_load(const char *file_path)
{
    u64   size = 0;
    FILE *file = fopen(file_path, "rb");
    if (file == NULL)
    {
        log_error("Failed to open file: %s\n", file_path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    void *buffer = malloc(size);
    if (buffer == NULL)
    {
        log_error("Failed to allocate memory for buffer\n");
        fclose(file);
        return NULL;
    }

    size_t result = fread(buffer, 1, size, file);
    if (result != size)
    {
        log_error("Failed to read file: %s\n", file_path);
        free(buffer);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return buffer;
}

Image *
asset_image_load(const char *file_path)
{
    Image *result = malloc(sizeof(Image));

    result->surface = IMG_Load(file_path);
    if (result == NULL)
    {
        log_error("Failed to load image: %s\n", IMG_GetError());
        return result;
    }

    CWindow *window = gfx_window_get();
    result->texture
        = SDL_CreateTextureFromSurface(window->renderer, result->surface);

    return result;
}

void
asset_image_unload(Image *image)
{
    SDL_FreeSurface(image->surface);
}

void
asset_image_size_get(Image *image, i16 *width, i16 *height)
{
    *width = image->surface->w;
    *height = image->surface->h;
}
