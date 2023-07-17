#include "core/core.h"

global_variable CSceneState *scene_state;

void
scene_startup(void)
{
    scene_state = MemoryAllocStruct(CSceneState);
    MemoryZeroStruct(scene_state, CSceneState);
}

void
scene_update(f32 dt)
{
}

void
scene_shutdown(void)
{
}

void
scene_clear(void)
{
}

void
scene_entity_add(CEntity *entity)
{
}

void
scene_entity_remove(CEntity *entity)
{
}
