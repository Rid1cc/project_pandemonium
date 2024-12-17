#include "../headers/settings_draw.h"
#include "../headers/globals.h"
#include "../headers/settings_update.h"
#include <raylib.h>
#include "../headers/settings_vars.h"
#include "sc_audio.h"
#include "sc_graphics.h"

void settings_button(std::string label ,bool &highl, Rectangle button, float xpos, float ypos){
    if(highl == true){
        DrawRectangleRec(button, ORANGE);
        DrawRectangleLinesEx(button, 3, BLACK);  
        DrawTextB(label.c_str(), ShakeXY(xpos, 1.5), ShakeXY(float(screenHeight)+ypos, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button, BLACK);
        DrawRectangleLinesEx(button, 3, ORANGE);
        DrawTextB(label.c_str(), xpos, float(screenHeight)+ypos, 40, ORANGE);
    }
}

void DrawSettings(float& general_volume, float& effects_volume) {
    ClearBackground(BLACK);

    //Borders
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    //ScreenShake + Barriers
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) == true){
        DrawRectangleLinesEx(ShakeRectangle(screen, 5), 6, ORANGE);
    }
    else{
        DrawRectangleLinesEx(screen, 3, ORANGE);
    }

    //Label
    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);  

    //Settings Left buttons
    settings_button("CUSTOM", custom_highl, button_custom, 110, -125);
    settings_button("DISPLAY", display_highl, button_display, 110, -205);
    settings_button("AUDIO", audio_highl, button_audio, 110, -285);
    settings_button("GRAPHICS", graph_highl, button_graphic, 110, -365);

    //Settings Right buttons
    settings_button("RETURN", return_highl, button_return, 990, -125);
    settings_button("APPLY", apply_highl, button_apply, 990, -205);
    settings_button("DEFAULT", restore_highl, button_restore, 990, -285);

    //Settings window
    DrawRectangleLinesEx(settings_screen, 3, ORANGE);

    switch (currentSettings) {
            case GRAPHICS: {
                HandleSetShader();
            } break;
            case AUDIO: {
                HandleSetAudio();
            } break;
            case DISPLAY: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case CUSTOM: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            default: break;
        }

    //Description window
    DrawRectangleLinesEx(settings_desc, 3, ORANGE);

    // DrawText(TextFormat("[V] V-Sync: %i", IsWindowState(FLAG_VSYNC_HINT)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 10, 20, ORANGE);
    // DrawText(TextFormat("[F] Window Maximized: %i", IsWindowState(FLAG_WINDOW_MAXIMIZED)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 40, 20, ORANGE);
    //DrawText(TextFormat("[M] Mute: %i", !(general_volume > 0.00000)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 70, 20, ORANGE);
    // DrawText(TextFormat("Mute Effects: %i", (effects_volume > 0)), GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 110, 20, ORANGE);
}