#include "settings_update.h"
#include "globals.h"
#include <raylib.h>

void SettingsUpdate(void) {
    if (IsKeyPressed(KEY_F)) ToggleFullscreen();

    if (IsKeyPressed(KEY_R)) // resizable option
    {
        if (IsWindowState(FLAG_WINDOW_RESIZABLE)) ClearWindowState(FLAG_WINDOW_RESIZABLE);
        else SetWindowState(FLAG_WINDOW_RESIZABLE);
    }

    if (IsKeyPressed(KEY_M))
    {
        // NOTE: Requires FLAG_WINDOW_RESIZABLE enabled!
        if (IsWindowState(FLAG_WINDOW_MAXIMIZED)) RestoreWindow();
        else MaximizeWindow();
    }

    if (IsKeyPressed(KEY_V))
    {
        if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
        else SetWindowState(FLAG_VSYNC_HINT);
    }
}

