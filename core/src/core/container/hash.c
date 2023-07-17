#include "core/core.h"

u64
hash_string_fnv1a64(const char *str)
{
    u64 hash = 5381;
    u32 c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
