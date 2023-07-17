#include "core/core.h"

#define DEBUG_COUNTERS_MAX 256

typedef struct DebugCycleCounter
{
    const char *name;
    u64         cycle_count;
    u64         hit_count;
} DebugCycleCounter;

typedef struct DebugCounterTable
{
    DebugCycleCounter counters[DEBUG_COUNTERS_MAX];
    u64               counters_count;
} DebugCounterTable;

struct CDebugState
{
    DebugCounterTable *counter_table;
};

global_variable CDebugState *debug_state;

DebugCycleCounter *debug_profiler_counter_add(const char *name);
DebugCycleCounter *debug_profiler_counter_find(const char *name);
u64                debug_string_to_hash(const char *str);

void
debug_profiler_init(void)
{
    debug_state                = MemoryAllocStruct(CDebugState);
    debug_state->counter_table = MemoryAllocStruct(DebugCounterTable);
    MemoryZeroStruct(debug_state->counter_table, DebugCounterTable);
}

void
debug_profiler_destroy(void)
{
    MemoryFree(debug_state->counter_table);
    MemoryFree(debug_state);
}

void
debug_profiler_handle(void)
{
    for (u64 index = 0; index < debug_state->counter_table->counters_count;
         index++)
    {
        DebugCycleCounter *counter
            = debug_state->counter_table->counters + index;
        if (counter->hit_count)
        {
            f64 dt = (f64)((f64)counter->cycle_count
                           / (f64)core_perf_frequency());

            f64 dt_cyh = (f64)(((f64)counter->cycle_count / counter->hit_count)
                               / (f64)core_perf_frequency());

#if 1
            log_info("%s: %lu/cy : %lu/h : %lu/cy/h : %.3f/ms : %.3f/cy/ms\n",
                     counter->name, counter->cycle_count, counter->hit_count,
                     counter->cycle_count / counter->hit_count,
                     dt * 1000000.0f, dt_cyh * 1000000.0f);
#endif
            counter->hit_count   = 0;
            counter->cycle_count = 0;
        }
    }
}

DebugCycleCounter *
debug_profiler_counter_add(const char *name)
{
    debug_state->counter_table
        ->counters[debug_state->counter_table->counters_count]
        .name
        = name;
    debug_state->counter_table->counters_count++;

    return &debug_state->counter_table
                ->counters[debug_state->counter_table->counters_count];
}

DebugCycleCounter *
debug_profiler_counter_find(const char *name)
{
    u64 hash = debug_string_to_hash(name);
    for (u64 i = 0; i < debug_state->counter_table->counters_count; i++)
    {
        if (hash
                == debug_string_to_hash(
                    debug_state->counter_table->counters[i].name)
            && strcmp(name, debug_state->counter_table->counters[i].name) == 0)
        {
            return &debug_state->counter_table->counters[i];
        }
    }
    return NULL;
}

u64
debug_string_to_hash(const char *str)
{
    u64 hash = 5381;
    u32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void *
_debug_profiler_timed_block_begin(const char *name)
{
    DebugCycleCounter *counter = debug_profiler_counter_find(name);
    if (counter == NULL)
    {
        counter = debug_profiler_counter_add(name);
    }

    return counter;
}

void
_debug_profiler_timed_block_end(void *counter_ptr, u64 cycle_count)
{
    DebugCycleCounter *counter = (DebugCycleCounter *)counter_ptr;
    counter->cycle_count += cycle_count;
    counter->hit_count++;
}
