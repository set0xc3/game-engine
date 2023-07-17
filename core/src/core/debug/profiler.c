#include "core/core.h"

#include "core/debug/internal.h"

void
debug_profiler_startup(void)
{
}

void
debug_profiler_shutdown(void)
{
}

void
debug_profiler_handle(void)
{
    for (u64 i = 0; i < debug_state.function_count; i++)
    {
        CDebugProfilerFunc *function = &debug_state.functions[i];
        if (function->hit_count)
        {
            f64 dt = (f64)((f64)function->cycle_count
                           / (f64)core_perf_frequency());

            f64 dt_cyh
                = (f64)(((f64)function->cycle_count / function->hit_count)
                        / (f64)core_perf_frequency());

#if 0
            log_info("%s: %lu/cy : %lu/h : %lu/cy/h : %.3f/ms : %.3f/cy/ms\n",
                     function->name, function->cycle_count,
                     function->hit_count,
                     function->cycle_count / function->hit_count,
                     dt * 1000000.0f, dt_cyh * 1000000.0f);
#endif
            function->hit_count   = 0;
            function->cycle_count = 0;
        }
    }
}

CDebugProfilerFunc *
debug_profiler_function_add(const char *func_name)
{
    debug_state.functions[debug_state.function_count].name = func_name;
    debug_state.function_count++;

    return &debug_state.functions[debug_state.function_count - 1];
}

CDebugProfilerFunc *
debug_profiler_function_find(const char *func_name)
{
    for (u64 i = 0; i < debug_state.function_count; i++)
    {
        if (strcmp(func_name, debug_state.functions[i].name) == 0)
        {
            return &debug_state.functions[i];
        }
    }

    return debug_profiler_function_add(func_name);
}

void *
_debug_profiler_timed_block_begin(const char *func_name)
{
    return debug_profiler_function_find(func_name);
}

void
_debug_profiler_timed_block_end(void *counter_ptr, u64 cycle_count)
{
    CDebugProfilerFunc *counter = (CDebugProfilerFunc *)counter_ptr;
    counter->cycle_count += cycle_count;
    counter->hit_count++;
}
