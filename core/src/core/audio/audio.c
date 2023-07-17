#include "core/core.h"

#include <SDL2/SDL_mixer.h>

typedef enum AudioSupport
{
    AUDIO_SUPPORT_WAVE,
    AUDIO_SUPPORT_COUNT
} AudioSupport;

global_variable const char *audio_ext_list[AUDIO_SUPPORT_COUNT] = {
    [AUDIO_SUPPORT_WAVE] = "wav",
};

struct CAudio
{
    bool       is_played;
    Mix_Music *music;
};

void
audio_init(void)
{
}

CAudio *
audio_load(const char *file_path)
{
#if 0
    AudioState *result = MemoryAllocStruct(AudioState);
    memset(result, 0, sizeof(AudioState));

    String8 *file_ext = str8_alloc(str8(file_path));
    str8_ext(file_ext, str8(file_path));

    bool is_found_ext = false;
    for (size_t i = 0; i < AUDIO_SUPPORT_COUNT; i += 1)
    {
        if (str8_eq(*file_ext, str8(audio_ext_list[i])))
        {
            is_found_ext = true;
            break;
        }
    }

    if (is_found_ext)
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            log_error("SDL_mixer could not initialize: %s\n", Mix_GetError());
        }

        result->music = Mix_LoadMUS(file_path);
        if (result->music == NULL)
        {
            MemoryFree(result);
            result = NULL;
            log_error("Failed Mix_LoadMUS: %s\n", Mix_GetError());
        }
    }
    else
    {
        log_warning("Format not supported: %s\n", str8_c(*file_ext));
    }

    str8_free(file_ext);
#endif

    return NULL;
}

void
audio_unload(CAudio *audio_state)
{
    if (audio_state == NULL)
    {
        return;
    }

    Mix_HaltMusic();
    Mix_FreeMusic(audio_state->music);
    MemoryFree(audio_state);
}

void
audio_play(CAudio *audio_state, bool loop)
{
    if (audio_state == NULL)
    {
        return;
    }

    if (!audio_state->is_played)
    {
        if (loop)
        {
            Mix_PlayMusic(audio_state->music, -1);
        }
        else
        {
            Mix_PlayMusic(audio_state->music, 0);
        }
        audio_state->is_played = true;
    }
}

void
audio_stop(CAudio *audio_state)
{
    if (audio_state == NULL)
    {
        return;
    }

    if (audio_state->is_played)
    {
        Mix_PauseMusic();
        audio_state->is_played = false;
    }
}
