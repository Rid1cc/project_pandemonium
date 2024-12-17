#include "../headers/settings_update.h"
#include "../headers/globals.h"
#include <raylib.h>
#include "../headers/settings_vars.h"
#include "../headers/shader_handler.h"

void SettingsUpdate(float& general_volume, float& effects_volume, bool& mute_audio) {

    /*
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
    */

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;

        //frames counter
    framesCounter ++;
    if(framesCounter>=60){
        framesCounter = 0;
    }

    //mouse pointer collision
    mousePos = GetMousePosition();
 
    //Highlight Handler
    switch (currentSettings) {
            case GRAPHICS: {
                graph_highl = true;
            } break;
            case AUDIO: {
                audio_highl = true;
            } break;
            case DISPLAY: {
                display_highl = true;
            } break;
            case CUSTOM: {
                custom_highl = true;
            } break;
            default: break;
        }
    
    //Button Graphic
    if(CheckCollisionPointRec(mousePos, button_graphic)==true){
        graph_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentSettings = GRAPHICS;
            graph_highl = true;
            }
    } else if (currentSettings != GRAPHICS )graph_highl = false;
    
    //Button Audio
    if(CheckCollisionPointRec(mousePos, button_audio)==true){
        audio_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentSettings = AUDIO;
            audio_highl = true;
            }
    } else if (currentSettings != AUDIO ) audio_highl = false;

    //Button Display
    if(CheckCollisionPointRec(mousePos, button_display)==true){
        display_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentSettings = DISPLAY;
        display_highl = true;
        }
    } else if (currentSettings != DISPLAY ) display_highl = false;

    //Button Custom
    if(CheckCollisionPointRec(mousePos, button_custom)==true){
        custom_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentSettings = CUSTOM;
        custom_highl = true;
        }
    } else if (currentSettings != CUSTOM ) custom_highl = false;

    //return
    if(CheckCollisionPointRec(mousePos, button_return)==true){
        printf("powrot\n");
        return_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = TITLE;
            return_highl = false;
            }
    } else return_highl = false;

    //apply
    if(CheckCollisionPointRec(mousePos, button_apply)==true){
        printf("apply\n");
        apply_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ReloadShader();
            }
    } else apply_highl = false;

    //restore
    if(CheckCollisionPointRec(mousePos, button_restore)==true){
        printf("restore\n");
        restore_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            restore_highl = false;
            }
    } else restore_highl = false;
}

