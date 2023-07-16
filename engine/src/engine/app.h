#ifndef APP_H
#define APP_H

#include <core/core.h>

typedef struct AppState
{
    b8        is_running;
    CLayer   *layer;
    CWindow  *window;
    CLibrary *game;
} AppState;

extern void app_layer(CLayer *layer);

internal void app_startup(void);
internal void app_shutdown(void);
internal void app_update(void);

internal b8 app_on_event(u32 code, CEvent event);

#endif // APP_H
