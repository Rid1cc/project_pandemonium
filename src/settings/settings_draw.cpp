#include "../headers/settings_draw.h"
#include "../headers/globals.h"
#include "../headers/settings_update.h"
#include <raylib.h>
#include "../headers/settings_vars.h"


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

    //Customize Button
    if(custom_highl == true){
        DrawRectangleRec(button_custom, ORANGE);
        DrawRectangleLinesEx(button_custom, 3, BLACK);
        DrawTextB("CUSTOM", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-125, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_custom, BLACK);
        DrawRectangleLinesEx(button_custom, 3, ORANGE);
        DrawTextB("CUSTOM", 110, float(screenHeight)-125, 40, ORANGE);
    }
    

    //Display Button
    if(display_highl == true){
        DrawRectangleRec(button_display, ORANGE);
        DrawRectangleLinesEx(button_display, 3, BLACK);
        DrawTextB("DISPLAY", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-205,1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_display, BLACK);
        DrawRectangleLinesEx(button_display, 3, ORANGE);
        DrawTextB("DISPLAY", 110, float(screenHeight)-205, 40, ORANGE);
    }

    //Audio Button
    if(audio_highl == true){
        DrawRectangleRec(button_audio, ORANGE);
        DrawRectangleLinesEx(button_audio, 3, BLACK);
        DrawTextB("AUDIO", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-285, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_audio, BLACK);
        DrawRectangleLinesEx(button_audio, 3, ORANGE);
        DrawTextB("AUDIO", 110, float(screenHeight)-285, 40, ORANGE);
    }

    //Graph Button
    if(graph_highl== true){
        DrawRectangleRec(button_graphic, ORANGE);
        DrawRectangleLinesEx(button_graphic, 3, BLACK);
        DrawTextB("GRAPHICS", ShakeXY(110, 1.5), ShakeXY(float(screenHeight)-365, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_graphic, BLACK);
        DrawRectangleLinesEx(button_graphic, 3, ORANGE);
        DrawTextB("GRAPHICS", 110, float(screenHeight)-365, 40, ORANGE);
    }

    //Return button
    if(return_highl== true){
        DrawRectangleRec(button_return, ORANGE);
        DrawRectangleLinesEx(button_return, 3, BLACK);
        DrawTextB("RETURN", ShakeXY(990, 1.5), ShakeXY(float(screenHeight)-125, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_return, BLACK);
        DrawRectangleLinesEx(button_return, 3, ORANGE);
        DrawTextB("RETURN", 990, float(screenHeight)-125, 40, ORANGE);
    }

    //Apply button
    if(apply_highl== true){
        DrawRectangleRec(button_apply, ORANGE);
        DrawRectangleLinesEx(button_apply, 3, BLACK);
        DrawTextB("APPLY", ShakeXY(990, 1.5), ShakeXY(float(screenHeight)-205, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_apply, BLACK);
        DrawRectangleLinesEx(button_apply, 3, ORANGE);
        DrawTextB("APPLY", 990, float(screenHeight)-205, 40, ORANGE);
    }

    //Restore button
    if(restore_highl== true){
        DrawRectangleRec(button_restore, ORANGE);
        DrawRectangleLinesEx(button_restore, 3, BLACK);
        DrawTextB("DEFAULT", ShakeXY(990, 1.5), ShakeXY(float(screenHeight)-285, 1.5), 40, BLACK);
    }
    else{
        DrawRectangleRec(button_restore, BLACK);
        DrawRectangleLinesEx(button_restore, 3, ORANGE);
        DrawTextB("DEFAULT", 990, float(screenHeight)-285, 40, ORANGE);
    }

    //Settings window
    DrawRectangleLinesEx(settings_screen, 3, ORANGE);

    switch (currentSettings) {
            case GRAPHICS: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case AUDIO: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
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