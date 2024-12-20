#include "raylib.h"
#include "headers/gameplay_update.h"
#include "headers/gameplay_draw.h"
#include "headers/settings_draw.h"
#include "headers/settings_update.h"
#include "headers/globals.h"
#include "headers/title_draw.h"
#include "headers/title_update.h"
#include "minigames/RotatingRectangleGame.h"
#include "minigames/ConnectWiresGame.h"
#include "minigames/FinderGame.h"
#include "headers/shader_handler.h"

int main(void) {


    InitWindow(screenWidth, screenHeight, "Pandemonium");
    SetWindowMinSize(screenWidth, screenHeight);
    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!
    SetTargetFPS(60);

    //FONT INIT, LOADING INTO VRAM
    alagard = LoadFont("../assets/fonts/alagard.png"); // For ui related
    pixeled = LoadFontEx("../assets/fonts/Minecraft.ttf", 16, 0, 317); //For system related

    //Shader init
    
    InitializeShader();

    //Initialize Scene, w. target
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    space3d = LoadRenderTexture((int)desc_window.width, (int)desc_window.height);

    //Load Shader
    //Shader shader = LoadShader(0, "../assets/shaders/fx.fs");
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
    //auto rotatingGame = std::make_shared<RotatingRectangleGame>(200, 150, 400, 300, "Rotating Rectangle");
    //gameManager.AddGame(rotatingGame);
    //auto finder = std::make_shared<FinderGame>(200, 150, 400, 300, "FinderGame");
    //gameManager.AddGame(finder);
    gameManager.SetTotalTime(15.0f);

    auto connectingGame = std::make_shared<ConnectWiresGame>(700, 250, 400, 300, "window 1");
    gameManager.AddGame(connectingGame);
    // auto rotatingGame = std::make_shared<RotatingRectangleGame>(700, 250, 400, 300, "Rotating Rectangle");
    // gameManager.AddGame(rotatingGame);

    

    //define camera state (for 3d models)
    camera.position = (Vector3){ 10.0f, 5.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Camera up vector
    camera.fovy = 45.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera mode type

    model_globe = LoadModel("../assets/models/globe.obj");
    model_cog = LoadModel("../assets/models/cog.obj");
    model_data = LoadModel("../assets/models/data.obj");
    model_door = LoadModel("../assets/models/door.obj");

    //auto rotatingGame = std::make_shared<RotatingRectangleGame>(screen.x + (screenWidth/2) - 200, screen.y + (screenHeight/2) - 150, 400, 300, "Rotating Rectangle");
    //gameManager.AddGame(rotatingGame);
    auto connectingGame2 = std::make_shared<ConnectWiresGame>(200, 150, 400, 300, "window 2");
    gameManager.AddGame(connectingGame2);

    while (!exitGame && !WindowShouldClose()) {
        Init3DTitleTexture();
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
                if (!connectingGame) {
                }
                UpdateGameplay(currentScreen, textBox, command, letterCount, mouseOnText, framesCounter, backTimer, history, upTimes);
            } break;
            case ENDING: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = TITLE;
            } break;
            default: break;
        }

        ClearBackground(RAYWHITE);
        
        // Begin 3D mode

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


        //Particles
        int randomW;
        int randomH;
        if(framesCounter%3==0){
        for(int i =0; i<=20; i++){
            std::uniform_int_distribution<int> rW(50, screenWidth-100);
            std::uniform_int_distribution<int> rH(25, screenHeight-50);
            randomW = rW(rng);
            randomH = rH(rng);
            DrawText("-", randomW, randomH, 10, ORANGE);
            }
        }
        Rectangle TextureKernel = { 0, 0, (float)target.texture.width, -(float)target.texture.height };
        EndTextureMode();
        BeginDrawing();
        ClearBackground(BLACK);
        //commented because of working with graphics, shaders just get in the way with that. 
        //to make it work uncomment beginshadermode and endshadermode.
        // BeginShaderMode(shader);  // <----- SHADER COMMENT
        DrawTextureRec(target.texture, ShakeRectangleOnClick(TextureKernel, 5), (Vector2){ 0, 0 }, WHITE);         
        // EndShaderMode(); // <----- SHADER COMMENT
        EndDrawing();
    }

    UnloadShader(shader);
    UnloadModel(model_cog);
    UnloadModel(model_door);
    UnloadModel(model_data);
    UnloadModel(model_globe);
    UnloadRenderTexture(target);
    UnloadRenderTexture(space3d);
    
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
