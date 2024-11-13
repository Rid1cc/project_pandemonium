#include "raylib.h"
#include "headers/gameplay_update.h"
#include "headers/gameplay_draw.h"
#include "headers/settings_draw.h"
#include "headers/settings_update.h"
#include "headers/globals.h"


int main(void) {


    InitWindow(screenWidth, screenHeight, "Pandemonium");
    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!
    SetTargetFPS(60);

    //FONT INIT, LOADING INTO VRAM
    alagard = LoadFont("../assets/fonts/alagard.png"); // For ui related
    pixeled = LoadFontEx("../assets/fonts/Pixeled.ttf", 20, 0, 317); //For system related

    /*
    // music initialization functions
    InitAudioDevice();
    if (IsAudioDeviceReady()) 
    {
    main_theme = LoadMusicStream("country.mp3");
    SetMasterVolume(general_volume);
    PlayMusicStream(main_theme);
    }
    */

    while (!WindowShouldClose()) {
        // UpdateMusicStream(main_theme);
        if (!IsWindowState(FLAG_WINDOW_RESIZABLE)) SetWindowState(FLAG_WINDOW_RESIZABLE);

        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 120) currentScreen = TITLE;
            } break;
            case TITLE: {
                if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
                if (IsKeyPressed(KEY_S)) currentScreen = SETTINGS;
            } break;
            case SETTINGS: {
                SettingsUpdate(general_volume, effects_volume, mute_audio);
            } break;
            case GAMEPLAY: {
                UpdateGameplay(currentScreen, textBox, command, letterCount, mouseOnText, framesCounter, backTimer, history, upTimes);
            } break;
            case ENDING: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = TITLE;
            } break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGO: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case TITLE: {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
                DrawLine(GetScreenWidth()/4, GetScreenHeight()/4, GetScreenWidth()/4, GetScreenHeight()/4 + 200, ORANGE);
                DrawText("TITLE SCREEN", 20, 20, 40, ORANGE);
                DrawText("PRESS ENTER to go to GAMEPLAY SCREEN", GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 10, 20, ORANGE);
                DrawText("PRESS S to go to SETTINGS SCREEN", GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 40, 20, ORANGE);
            } break;
            case SETTINGS: {
                DrawSettings(general_volume, effects_volume);
            } break;
            case GAMEPLAY: {
                DrawGameplay(textBox, command, letterCount, mouseOnText, framesCounter, historyDrawn);
            } break;
            case ENDING: {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
            } break;
            default: break;
        }

        EndDrawing();
    }

    /*
    // Music De-Initialization
    UnloadMusicStream(main_theme);
    CloseAudioDevice();
    CloseWindow();
    return 0;
    */

    CloseWindow();
    return 0;
}
