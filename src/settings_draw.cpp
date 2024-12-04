#include "headers/settings_draw.h"
#include "headers/globals.h"
#include <raylib.h>

void DrawSettings(float& general_volume, float& effects_volume) {
    ClearBackground(BLACK);

    DrawLine(GetScreenWidth()/4, GetScreenHeight()/4, GetScreenWidth()/4, GetScreenHeight()/4 + 200, ORANGE);
    // DrawRectangleLines(GetScreenWidth()/4, GetScreenHeight()/4, GetScreenWidth()/2, GetScreenHeight()/2, ORANGE);

    DrawText(TextFormat("[V] V-Sync: %i", IsWindowState(FLAG_VSYNC_HINT)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 10, 20, ORANGE);
    DrawText(TextFormat("[F] Window Maximized: %i", IsWindowState(FLAG_WINDOW_MAXIMIZED)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 40, 20, ORANGE);
    //DrawText(TextFormat("[M] Mute: %i", !(general_volume > 0.00000)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 70, 20, ORANGE);
    // DrawText(TextFormat("Mute Effects: %i", (effects_volume > 0)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 110, 20, ORANGE);
}