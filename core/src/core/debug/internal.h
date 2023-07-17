#ifndef CORE_DEBUG_INTERNAL_H
#define CORE_DEBUG_INTERNAL_H

#include "core/core.h"

#define MEMORY_BLOCKS_MAX      1000
#define PROFILER_FUNCTIONS_MAX 1000

typedef struct CDebugMemoryBlock
{
    void       *memory;
    u64         size;
    const char *file_path;
    u32         line;
} CDebugMemoryBlock;

typedef struct CDebugProfilerFunc
{
    const char *name;
    u64         cycle_count;
    u64         hit_count;
} CDebugProfilerFunc;

struct CDebugState
{
    CDebugMemoryBlock memory_blocks[MEMORY_BLOCKS_MAX];
    u64               memory_block_count;

    CDebugProfilerFunc functions[PROFILER_FUNCTIONS_MAX];
    u64                function_count;
};

global_variable CDebugState debug_state;

// Profiler Interface

void debug_profiler_startup(void);
void debug_profiler_shutdown(void);
void debug_profiler_handle(void);

CDebugProfilerFunc *debug_profiler_function_add(const char *func_name);
CDebugProfilerFunc *debug_profiler_function_find(const char *func_name);

#endif // CORE_DEBUG_INTERNAL_H
