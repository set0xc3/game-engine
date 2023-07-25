#include <core/core.h>

typedef struct GameState
{
} GameState;

global_variable GameState game_state;

CEXPORT void
startup(void)
{
    PROFILER_BEGIN(game_startup);

    log_info("Game: startup\n");
    PROFILER_END(game_startup);

    CEntity *entity = scene_entity_create();
    scene_entity_destroy(entity);
}

CEXPORT void
update(f32 dt)
{
    local_variable b8 first_init = false;
    if (first_init == false)
    {
        first_init = true;
        log_info("Game: update\n");
    }
}

CEXPORT void
shutdown(void)
{
    log_info("Game: shutdown\n");
}

// TODO: remove this
void
layer_main(CLayer *layer)
{
}
