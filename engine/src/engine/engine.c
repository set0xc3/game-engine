#include "engine/app.h"

#include "engine/app.c"

int
main(int argc, char *argv[])
{
    debug_startup();
    app_update();
    debug_shutdown();

    return 0;
}
