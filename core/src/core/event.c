#include "core/core.h"

#define EVENT_MAX 16384
#define REGISTERED_MAX 16384

typedef struct EventRegitered
{
    void             *listener;
    event_fn_on_event callback;
} EventRegitered;

typedef struct EventEntry
{
    EventRegitered *events;
    u64             events_count;
} EventEntry;

typedef struct EventState
{
    EventEntry *registered;
    u64         registered_count;
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

    event_state = calloc(sizeof(EventState), 1);
    event_state->registered = calloc(sizeof(EventEntry), REGISTERED_MAX);
    event_state->registered->events
        = calloc(sizeof(EventRegitered), EVENT_MAX);

    is_initialized = true;
    return true;
}

b8
event_shutdown(void)
{
    return true;
}

b8
event_register(u32 code, void *listener, event_fn_on_event on_event)
{
    if (!is_initialized)
    {
        return false;
    }

    if (event_state->registered_count + 1 > REGISTERED_MAX)
    {
        return false;
    }

    if (event_state->registered[code].events == NULL)
    {
        event_state->registered[code].events
            = calloc(sizeof(EventRegitered), 1);
        event_state->registered_count++;
    }

    EventRegitered *event = event_state->registered[code].events
                            + event_state->registered[code].events_count;
    if (event->listener != listener)
    {
        event->listener = listener;
        event->callback = on_event;
        event_state->registered[code].events_count++;
    }

    return true;
}

b8
event_unregister(u32 code, void *listener, event_fn_on_event on_event)
{
    if (!is_initialized)
    {
        return false;
    }

    return true;
}

b8
event_fire(u32 code, void *sender, CEvent event)
{
    if (!is_initialized)
    {
        return false;
    }

    if (event_state->registered[code].events == NULL)
    {
        return false;
    }

    for (u64 i = 0; i < event_state->registered_count; i++)
    {
        EventRegitered e = event_state->registered[code].events[i];
        if (e.callback(code, sender, e.listener, event))
        {
            return true;
        }
    }

    return false;
}
