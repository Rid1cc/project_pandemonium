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
#include "logoscreen/logo_screen.h"


int main(void) {

    // Core initialization
    InitWindow(screenWidth, screenHeight, "Pandemonium");
    SetWindowMinSize(screenWidth, screenHeight);
    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!
    SetTargetFPS(60);

    // Get the assets path
    assetsPath = getAssetsPath();

    //FONT INIT, LOADING INTO VRAM
    alagard = LoadFont((assetsPath + "fonts/alagard.png").c_str()); // For ui related
    pixeled = LoadFontEx((assetsPath + "fonts/Minecraft.ttf").c_str(), 16, 0, 317); //For system related    
    
    // Initialize shader
    InitializeShader();

    //Initialize Scene, w. target
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    space3d = LoadRenderTexture((int)desc_window.width, (int)desc_window.height);

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

    // Init Logo Screen
    InitLogoScreen();

    // Minigames decs
    auto connectingGame = std::make_shared<ConnectWiresGame>(700, 250, 400, 300, "window 1");
    auto finder = std::make_shared<FinderGame>(200, 150, 400, 300, "FinderGame");
    
    // Add games to the game manager
    gameManager.AddGame(finder);
    gameManager.SetTotalTime(15.0f);
    gameManager.AddGame(connectingGame);

    //define camera state (for 3d models)
    camera.position = (Vector3){ 10.0f, 5.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Camera up vector
    camera.fovy = 45.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera mode type

    // Load 3d models
    model_globe = LoadModel((assetsPath + "models/globe.obj").c_str());
    model_cog = LoadModel((assetsPath + "models/cog.obj").c_str());
    model_data = LoadModel((assetsPath + "models/data.obj").c_str());
    model_door = LoadModel((assetsPath + "models/door.obj").c_str());

    // Main game loop
    while (!exitGame && !WindowShouldClose()) {
       
        Init3DTitleTexture();
        BeginTextureMode(target);

        //Update mouse
        mousePos = MapMouseToFlat(GetMousePosition(), {1280.0, 720.0});

        // UpdateMusicStream(main_theme);
        if (!IsWindowState(FLAG_WINDOW_RESIZABLE)) SetWindowState(FLAG_WINDOW_RESIZABLE);

        switch (currentScreen) {
            case LOGO: {
                UpdateLogoScreen();
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

        switch (currentScreen) {
            case LOGO: {
                DrawLogoScreen();
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

        TextureKernel = { 0, 0, (float)target.texture.width, -(float)target.texture.height };
        EndTextureMode();

        //Main Shader drawing, texture linking
        BeginDrawing();
        ClearBackground(BLACK);
        BeginShaderMode(shader);  
            DrawTextureRec(target.texture, ShakeRectangleOnClick(TextureKernel, 5), (Vector2){ 0, 0 }, WHITE);
        EndShaderMode(); 
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
