#include "core/core.h"

#ifdef PLATFORM_LINUX
#include <uuid/uuid.h>
#endif

char *
uuid_gen(void)
{
    char *uuid = NULL;
#ifdef PLATFORM_LINUX
    uuid_t binuuid;
    uuid_generate_random(binuuid);
    uuid = MemoryAllocArray(char, 37);
    uuid_unparse_upper(binuuid, uuid);
#endif
    return uuid;
}
