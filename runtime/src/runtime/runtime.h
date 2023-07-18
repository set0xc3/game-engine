#ifndef RUNTIME_H
#define RUNTIME_H

#include <core/core.h>

typedef struct RuntimeState
{
} RuntimeState;

internal void runtime_startup(void);
internal void runtime_update(f32 dt);
internal void runtime_shutdown(void);

internal b8 runtime_on_event(u32 code, CEvent event);

#endif // RUNTIME_H
