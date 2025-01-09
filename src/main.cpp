#include "raylib.h"
#include "headers/gameplay_update.h"
#include "headers/gameplay_draw.h"
#include "gameplay/gameplay_vars.h"
#include "headers/settings_draw.h"
#include "headers/settings_update.h"
#include "headers/globals.h"
#include "headers/title_draw.h"
#include "headers/title_update.h"
#include "headers/DifficultySelector.h"
#include "minigames/RotatingRectangleGame.h"
#include "minigames/ConnectWiresGame.h"
#include "minigames/FinderGame.h"
#include "minigames/TypeGame.h"
#include "minigames/BallGame.h"
#include "headers/shader_handler.h"
#include "logoscreen/logo_screen.h"
#include "headers/settings_vars.h"
#include "headers/data_draw.h"
#include "headers/data_update.h"


int main(void) {
    
    primaryColor = ORANGE;

    // Core initialization
    InitWindow(screenWidth, screenHeight, "Pandemonium");
    SetWindowMinSize(screenWidth, screenHeight);
    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!
    SetTargetFPS(60);

    // Get the assets path
    assetsPath = getSubfolderPath("assets");
    configPath = getSubfolderPath("config");

    //FONT INIT, LOADING INTO VRAM
    alagard = LoadFont((assetsPath + "fonts/alagard.png").c_str()); // For ui related
    pixeled = LoadFontEx((assetsPath + "fonts/Minecraft.ttf").c_str(), 16, 0, 317); //For system related    
    
    // Initialize shader
    InitializeShader();

    //Initialize Scene, w. target
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    space3d = LoadRenderTexture((int)desc_window.width, (int)desc_window.height);

    Texture2D botnetTexture = LoadTexture("../assets/images/botnet.png");
    Texture2D ddosTexture = LoadTexture("../assets/images/ddos.png");
    Texture2D mailbombTexture = LoadTexture("../assets/images/mailbomb.png");
    
    // music initialization functions
    InitAudioDevice();
    main_theme = LoadMusicStream("../assets/audio/maintheme_pandemonium.wav");
    game_theme = LoadMusicStream("../assets/audio/song2.wav");
    PlayMusicStream(main_theme); 
    PlayMusicStream(game_theme);   
    

    // Init Logo Screen
    InitLogoScreen();

    //gameplayManager.gameplayInit();

    // // Minigames decs
    //auto connectingGame = std::make_shared<ConnectWiresGame>(700, 250, 400, 300,"window 1");
   // auto type = std::make_shared<TypeGame>(150, 120, 1000, 400, "TypeGame");
   // miniGamesManager.AddGame(type);
    //auto finder = std::make_shared<FinderGame>(200, 150, 400, 300, "FinderGame");
    //auto bouncingballGame = std::make_shared<BallGame>(300,200,600,500, "Ball Game");
    //miniGamesManager.AddGame(bouncingballGame);
    // // Add games to the game manager
    //miniGamesManager.AddGame(finder);
    // miniGamesManager.SetTotalTime(900.0f);
    //miniGamesManager.AddGame(connectingGame);

    //define camera state (for 3d models)
    camera.position = (Vector3){ 10.0f, 5.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Camera up vector
    camera.fovy = 45.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera mode type

    // Load 3d models
    model_globe = LoadModel((assetsPath + "models/globe.obj").c_str());
    model_cog = LoadModel((assetsPath + "models/cog.obj").c_str());
    model_door = LoadModel((assetsPath + "models/door.obj").c_str());

    // Main game loop
    while (!exitGame && !WindowShouldClose()) {
        Init3DTitleTexture();
        BeginTextureMode(target);
        //Theme
        SetMusicVolume(main_theme, music_volume);
        SetMusicVolume(game_theme, music_volume);

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
                UpdateMusicStream(main_theme);
            } break;
            case SETTINGS: {
                SettingsUpdate(general_volume, effects_volume, mute_audio);
            } break;
            case DIFFICULTY_SELECTION: {
                UpdateDifficultySelection();
            } break;
            case GAMEPLAY: {
                UpdateGameplay(currentScreen, textBox, command, letterCount, mouseOnText, framesCounter, backTimer, history, upTimes);
                UpdateMusicStream(game_theme);
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
            case DATA_LORE: {
                DrawData();
            } break;
            case DIFFICULTY_SELECTION: {
                DrawDifficultySelection();
            } break;
            case GAMEPLAY: {
                DrawTextureEx(botnetTexture, {botnetIcon.x, botnetIcon.y}, 0.0f, 1.75f, WHITE);
                DrawTextureEx(ddosTexture, {ddosIcon.x, ddosIcon.y}, 0.0f, 1.75f, WHITE);
                DrawTextureEx(mailbombTexture, {mailbombIcon.x, mailbombIcon.y}, 0.0f, 1.75f, WHITE);
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
            DrawText("-", randomW, randomH, 10, primaryColor);
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
    UnloadModel(model_globe);
    UnloadTexture(botnetTexture);
    UnloadRenderTexture(target);
    UnloadRenderTexture(space3d);
    
    
    // Music De-Initialization
    UnloadMusicStream(main_theme);
    UnloadMusicStream(game_theme);
    CloseAudioDevice();
    CloseWindow();
    return 0;
    

    CloseWindow();
    return 0;
}
