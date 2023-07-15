#include "core/core.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

struct MemoryArena
{
    u8 *data;
    u64 size;
    u64 pos;
};

struct MemoryArenaTemp
{
    MemoryArena *arena;
    u64          pos;
};

MemoryArena *
arena_create(u64 size)
{
    MemoryArena *arena = malloc(sizeof(MemoryArena));
    arena->data = malloc(size);
    arena->size = size;
    arena->pos = 0;
    return arena;
}

void
arena_destroy(MemoryArena *arena)
{
    free(arena->data);
    free(arena);
}

void *
arena_push(MemoryArena *arena, u64 size)
{
    if (arena->pos + size > arena->size)
    {
        log_error("Handle out-of-memory\n");
        assert(true);
    }

    u8 *pos = (u8 *)arena->data + arena->pos;
    arena->pos += size;
    return pos;
}

void *
arena_push_zero(MemoryArena *arena, u64 size)
{
    void *memory = arena_push(arena, size);
    memset(memory, 0, size);
    return memory;
}

void *
arena_pop(MemoryArena *arena, u64 size)
{
    if (arena->pos == 0)
    {
        log_error("Handle out-of-memory\n");
        assert(true);
    }

    arena->pos -= size;
    u8 *pos = (u8 *)arena->pos - size;
    return pos;
}

void
arena_clear(MemoryArena *arena)
{
    arena->pos = 0;
}

u64
arena_offset_get(MemoryArena *arena)
{
    return arena->pos;
}

MemoryArenaTemp
arena_temp_begin(MemoryArena *arena)
{
    MemoryArenaTemp result = { 0 };
    result.arena = arena;
    result.pos = arena->pos;
    return result;
}

void
arena_temp_end(MemoryArenaTemp temp)
{
    temp.arena->pos = temp.pos;
}

MemoryArenaTemp
arena_temp_scratch_get(MemoryArena *arena)
{
    MemoryArenaTemp temp = { 0 };
    temp.arena = arena;
    temp.pos = arena->pos;
    return temp;
}
