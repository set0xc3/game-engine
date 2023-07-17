#include "core/core.h"

#define EVENT_LISTENERS_MAX 256

typedef struct CEventListener
{
    u32               code;
    event_on_listener callback;
} CEventListener;

typedef struct CEventState
{
    CEventListener *listeners;
    u64             listeners_count;
} CEventState;

global_variable b8           is_initialized;
global_variable CEventState *event_state;

b8
event_startup(void)
{
    if (is_initialized)
    {
        return false;
    }

    event_state = MemoryAllocStruct(CEventState);
    MemoryZeroStruct(event_state, CEventState);

    event_state->listeners
        = MemoryAllocArray(CEventListener, EVENT_LISTENERS_MAX);
    MemoryZeroArray(event_state->listeners, CEventListener,
                    EVENT_LISTENERS_MAX);

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
    if (!is_initialized
        || event_state->listeners_count + 1 > EVENT_LISTENERS_MAX)
    {
        return false;
    }

    for (u64 index = 0; index < event_state->listeners_count; index++)
    {
        CEventListener *listener = event_state->listeners + index;
        if (listener->code & code && listener->callback == on_listener)
        {
            return true;
        }
    }

    CEventListener *listener
        = event_state->listeners + event_state->listeners_count;
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

    CEventListener *top_listener
        = event_state->listeners + event_state->listeners_count - 1;
    for (u64 index = 0; index < event_state->listeners_count; index++)
    {
        CEventListener *listener = event_state->listeners + index;
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
        CEventListener *listener = event_state->listeners + index;
        if (listener->code & code && listener->callback(code, event))
        {
            break;
        }
    }

    return true;
}
