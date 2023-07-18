#include <core/core.h>

API void
startup(void)
{
    PROFILER_BEGIN(game_startup);
    log_info("Game: startup\n");
    PROFILER_END(game_startup);
}

API void
update(f32 dt)
{
    local_variable b8 first_init = false;
    if (first_init == false)
    {
        first_init = true;
        log_info("Game: update\n");
    }
}

API void
shutdown(void)
{
    log_info("Game: shutdown\n");
}
