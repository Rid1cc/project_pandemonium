#include "raylib.h"
#include "headers/gameplay_update.h"
#include "headers/gameplay_draw.h"
#include "headers/settings_draw.h"
#include "headers/settings_update.h"
#include "headers/globals.h"
#include "headers/title_draw.h"
#include "headers/title_update.h"
#include "minigames/RotatingRectangleGame.h"
#include "minigames/FinderGame.h"



int main(void) {


    InitWindow(screenWidth, screenHeight, "Pandemonium");
    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!
    SetTargetFPS(60);

    //FONT INIT, LOADING INTO VRAM
    alagard = LoadFont("../assets/fonts/alagard.png"); // For ui related
    pixeled = LoadFontEx("../assets/fonts/Minecraft.ttf", 16, 0, 317); //For system related

    //Initialize Scene, w. target
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    //Load Shader
    Shader shader = LoadShader(0, "../assets/shaders/fx.fs");
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

    //minigames init
    auto rotatingGame = std::make_shared<RotatingRectangleGame>(200, 150, 400, 300, "Rotating Rectangle");
    // gameManager.AddGame(rotatingGame);

    auto finder = std::make_shared<FinderGame>(200, 150, 400, 300, "FinderGame");
    gameManager.AddGame(finder);

    while (!WindowShouldClose()) {

        BeginTextureMode(target);
        // UpdateMusicStream(main_theme);
        if (!IsWindowState(FLAG_WINDOW_RESIZABLE)) SetWindowState(FLAG_WINDOW_RESIZABLE);

        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 120) currentScreen = TITLE;
            } break;
            case TITLE: {
                TitleUpdate();
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

        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGO: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case TITLE: {
                DrawTitle();
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
        EndTextureMode();
        BeginDrawing();

        ClearBackground(BLACK);

        //commented because of working with graphics, shaders just get in the way with that. 
        //to make it work uncomment beginshadermode and endshadermode.

        //BeginShaderMode(shader);  // <----- SHADER COMMENT
        DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height }, (Vector2){ 0, 0 }, WHITE);
        //EndShaderMode(); // <----- SHADER COMMENT

        EndDrawing();
    }

    UnloadShader(shader);
    UnloadRenderTexture(target);
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
