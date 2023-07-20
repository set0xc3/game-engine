#include "core/core.h"

global_variable CSceneState *scene_state;

void
scene_startup(void)
{
    scene_state = MemoryAllocStruct(CSceneState);
    MemoryZeroStruct(scene_state, CSceneState);

    scene_state->entities = MemoryAllocArray(CEntity, SCENE_ENTITIES_MAX);
    MemoryZeroArray(scene_state->entities, CEntity, SCENE_ENTITIES_MAX);

    scene_state->entities_selected
        = MemoryAllocArray(CEntityID, SCENE_ENTITIES_MAX);
    MemoryZeroArray(scene_state->entities_selected, CEntityID,
                    SCENE_ENTITIES_MAX);
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

CEntity *
scene_entity_create(void)
{
    CEntity *result = scene_state->entities + scene_state->entities_count;
    result->uuid    = uuid_gen();
    result->scale   = v3(1.0f, 1.0f, 1.0f);
    result->flags   = EntityFlag_Everything;
    scene_state->entities_count++;
    return result;
}

void
scene_entity_destroy(CEntity *entity)
{
    scene_state->entities_count--;
    MemoryFree(entity->uuid);
    MemoryCopyStruct(entity, &scene_state->entities_count - 1, CEntity);
    // MemoryZeroStruct(entity, CEntity);
}
