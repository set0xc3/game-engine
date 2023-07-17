#include "core/core.h"

#include "core/debug/internal.h"

void
debug_memory_handle(void)
{
    u64 memory_used = 0;

    for (u64 i = 0; i < debug_state.memory_block_count; i++)
    {
        CDebugMemoryBlock *block = &debug_state.memory_blocks[i];
        if (block->memory)
        {
            memory_used += block->size;

            // log_info("memory.block: %s:%lu\n", block->file_path,
            // block->line);
        }
    }

    log_debug("memory.total     (0)\n");
    log_debug("memory.used      (%ld)\n", memory_used);
    log_debug("memory.available (0)\n");
    log_debug("memory.cached    (0)\n");
    log_debug("memory.freed     (0)\n");
}

void *
_debug_memory_alloc(u64 size, const char *file_path, u64 line)
{
    void *memory = malloc(size);
    if (memory == NULL)
    {
        log_error("Failed allocate memory\n");
    }

    if (debug_state.memory_block_count < MEMORY_BLOCKS_MAX)
    {
        CDebugMemoryBlock *block
            = &debug_state.memory_blocks[debug_state.memory_block_count];
        block->memory    = memory;
        block->size      = size;
        block->file_path = file_path;
        block->line      = line;
        debug_state.memory_block_count++;

        // log_info("memory.alloced: %s:%lu\n", block->file_path, block->line);
    }

    return memory;
}

void
_debug_memory_free(void *memory, const char *file_path, u64 line)
{
    if (debug_state.memory_block_count > 0)
    {
        CDebugMemoryBlock *top_block
            = &debug_state.memory_blocks[debug_state.memory_block_count - 1];

        for (u64 i = 0; i < debug_state.memory_block_count; i++)
        {
            CDebugMemoryBlock *block = &debug_state.memory_blocks[i];

            if (block->memory == memory)
            {
                memcpy(block, top_block, sizeof(CDebugMemoryBlock));
                debug_state.memory_block_count--;

                // log_info("memory.freed: %s:%lu\n", file_path, line);
                break;
            }
        }
    }

    free(memory);
}

void
_debug_memory_zero(void *memory, u64 size, const char *file_path, u64 line)
{
    memset(memory, 0, size);

    // log_info("memory.zero: %s:%lu\n", file_path, line);
}
