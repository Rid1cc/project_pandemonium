#include "headers/settings_update.h"
#include "headers/globals.h"
#include <raylib.h>

void SettingsUpdate(float& general_volume, float& effects_volume, bool& mute_audio) {
    
    if (IsKeyPressed(KEY_V))
    {
        if (IsWindowState(FLAG_VSYNC_HINT)) ClearWindowState(FLAG_VSYNC_HINT);
        else SetWindowState(FLAG_VSYNC_HINT);
    }

    if (IsKeyPressed(KEY_F))
    {
        if (!IsWindowMaximized()) SetWindowState(FLAG_WINDOW_MAXIMIZED);
        else if (IsWindowMaximized()) RestoreWindow();
    }

    if (IsKeyPressed(KEY_M)) {
        if (!mute_audio) {PauseMusicStream(main_theme); general_volume = 0.0f; mute_audio = true;}
        else if (mute_audio) {ResumeMusicStream(main_theme); effects_volume = 1.0f; mute_audio = false;}
    }

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
}

