#ifndef CORE_INTERNAL_H
#define CORE_INTERNAL_H

#include "core/core.h"

struct CCoreState
{
    CLayer       layer;
    CWindow     *window;
    CLibrary     game_dll;
    CSceneState *scene_state;
};

#endif // CORE_INTERNAL_H
