#include "core/core.h"

#include <SDL2/SDL.h>

CLibrary *
library_load(const char *path)
{
    CLibrary *result = MemoryAllocStruct(CLibrary);
    MemoryZeroStruct(result, CLibrary);

    char *dot      = ".";
    u64   dot_size = strlen(dot);

    u64      size     = strlen(path) + strlen(PLATFORM_LIB_EXT) + dot_size;
    CString8 path_ext = { (u8 *)alloca(size), size };
    strncpy((char *)path_ext.str, path, path_ext.size);

    strncat((char *)path_ext.str, dot, path_ext.size);
    strncat((char *)path_ext.str, PLATFORM_LIB_EXT, path_ext.size);

    result->handle = SDL_LoadObject((const char *)path_ext.str);

    return result;
}

void
library_unload(CLibrary *library)
{
    SDL_UnloadObject(library->handle);
    MemoryFree(library);
}

void *
library_load_function(CLibrary *library, const char *name)
{
    return SDL_LoadFunction(library->handle, name);
}
