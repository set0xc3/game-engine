#include "core/core.h"

#define LISTENERS_MAX 256

typedef struct Listener
{
    u32               code;
    event_on_listener callback;
} Listener;

typedef struct EventState
{
    Listener *listeners;
    u64       listeners_count;
} EventState;

global_variable b8          is_initialized;
global_variable EventState *event_state;

b8
event_startup(void)
{
    if (is_initialized)
    {
        return false;
    }

    event_state = MemoryAllocStruct(EventState);
    MemoryZeroStruct(event_state, EventState);

    event_state->listeners = MemoryAllocArray(Listener, LISTENERS_MAX);
    MemoryZeroStruct(event_state->listeners, Listener);

    is_initialized = true;
    return true;
}

b8
event_shutdown(void)
{
    MemoryFree(event_state->listeners);
    MemoryFree(event_state);
    return true;
}

b8
event_register(u32 code, event_on_listener on_listener)
{
    if (!is_initialized || event_state->listeners_count + 1 > LISTENERS_MAX)
    {
        return false;
    }

    for (u64 index = 0; index < event_state->listeners_count; index++)
    {
        Listener *listener = event_state->listeners + index;
        if (listener->code & code && listener->callback == on_listener)
        {
            return true;
        }
    }

    Listener *listener = event_state->listeners + event_state->listeners_count;
    listener->code     = code;
    listener->callback = on_listener;
    event_state->listeners_count++;

    return true;
}

b8
event_unregister(u32 code, event_on_listener on_listener)
{
    if (!is_initialized)
    {
        return false;
    }

    Listener *top_listener
        = event_state->listeners + event_state->listeners_count - 1;
    for (u64 index = 0; index < event_state->listeners_count; index++)
    {
        Listener *listener = event_state->listeners + index;
        if (listener->code & code && listener->callback == on_listener)
        {
            listener->code     = top_listener->code;
            listener->callback = top_listener->callback;
            event_state->listeners_count--;

            break;
        }
    }

    return true;
}

b8
event_fire(u32 code, CEvent event)
{
    if (!is_initialized)
    {
        return false;
    }

    for (u64 index = 0; index < event_state->listeners_count; index++)
    {
        Listener *listener = event_state->listeners + index;
        if (listener->code & code && listener->callback(code, event))
        {
            break;
        }
    }

    return true;
}
