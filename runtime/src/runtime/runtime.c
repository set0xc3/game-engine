#include "runtime/runtime.h"

global_variable RuntimeState runtime_state;

void
runtime_startup(void)
{
    log_info("Runtime: startup\n");
}

void
runtime_update(f32 dt)
{
    local_variable b8 first_init = false;
    if (first_init == false)
    {
        first_init = true;
        log_info("Update: update\n");
    }
}

void
runtime_shutdown(void)
{
    log_info("Runtime: shutdown\n");
}

void
layer_main(CLayer *layer)
{
    layer->api.startup  = runtime_startup;
    layer->api.update   = runtime_update;
    layer->api.shutdown = runtime_shutdown;
}
