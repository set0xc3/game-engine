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
global_variable EventState *state;

b8
event_init(void)
{
    if (is_initialized)
    {
        return false;
    }

    state = calloc(sizeof(EventState), 1);

    is_initialized = true;
    return true;
}

b8
event_destroy(void)
{
    return true;
}

b8
event_register(u16 code, void *listener, event_fn_on_event on_event)
{
    if (!is_initialized)
    {
        return false;
    }

    if (state->registered_count + 1 > REGISTERED_MAX)
    {
        return false;
    }

    if (state->registered[code].events == NULL)
    {
        state->registered[code].events = calloc(sizeof(EventRegitered), 1);
        state->registered_count++;
    }

    EventRegitered *event = state->registered[code].events
                            + state->registered[code].events_count;
    if (event->listener != listener)
    {
        event->listener = listener;
        event->callback = on_event;
        state->registered[code].events_count++;
    }

    return true;
}

b8
event_unregister(u16 code, void *listener, event_fn_on_event on_event)
{
    if (!is_initialized)
    {
        return false;
    }

    return true;
}

b8
event_fire(u16 code, void *sender, EventCtx context)
{
    if (!is_initialized)
    {
        return false;
    }

    return true;
}
