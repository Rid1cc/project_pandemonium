#include "../headers/settings_update.h"
#include "../headers/globals.h"
#include <raylib.h>
#include "../headers/settings_vars.h"

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
    /*
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

    //check if mouse over button
    
    //play
    if(CheckCollisionPointRec(mousePos, button_graphic)==true){
        printf("graj\n");
        graph_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = GAMEPLAY;
            graph_highl = false;
            }
    } else graph_highl = false;
    
    //settings
    if(CheckCollisionPointRec(mousePos, button_audio)==true){
        printf("opcje\n");
        audio_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentScreen = SETTINGS;
            audio_highl = false;
            }
    } else audio_highl = false;

    //lore
    if(CheckCollisionPointRec(mousePos, button_display)==true){
        printf("lore\n");
        display_highl = true;
    } else display_highl = false;

    //quit
    if(CheckCollisionPointRec(mousePos, button_custom)==true){
        printf("quit\n");
        custom_highl = true;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            exitGame = true;
            }
    } else custom_highl = false;

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
            apply_highl = false;
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

