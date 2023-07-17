#include "core/core.h"

#include "core/debug/internal.h"

void
debug_startup(void)
{
    debug_profiler_startup();
}

void
debug_shutdown(void)
{
    debug_profiler_shutdown();
    debug_memory_handle();
}

void
debug_update(void)
{
    debug_profiler_handle();
}
