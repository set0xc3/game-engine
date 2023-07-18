#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "core/core.h"

typedef struct CCoreState
{
    CLayer    layer;
    CWindow  *window;
    CLibrary *game;

} CCoreState;

global_variable CCoreState *core_state;

#endif // CORE_INTERNAL_H
