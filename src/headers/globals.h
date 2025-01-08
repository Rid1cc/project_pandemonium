#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"    
#include "MiniGameManager.h" 
#include <string>
#include <random>
#include <chrono>
#include <iostream>
#include <string>
#include "../managers/FileSystemManager.h"
#include "../managers/EventManager.h"
#include "../managers/GameplayManager.h"
#include "DifficultySelector.h"

#if defined(_WIN32)
    // #include <windows.h> // Removed to prevent conflicts
    #include "raylib.h"
    
    // Define necessary Windows types manually
    typedef void* HMODULE;
    typedef char* LPSTR;
    typedef unsigned long DWORD; // Added definition for DWORD
    #define WINAPI __stdcall     // Added definition for WINAPI
    
    // Declare only GetModuleFileNameA
    extern "C" __declspec(dllimport) DWORD WINAPI GetModuleFileNameA(HMODULE hModule, LPSTR lpFilename, DWORD nSize);
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#else
    #include <dlfcn.h>
    #include <unistd.h>
#endif

typedef enum GameScreen { LOGO = 0, TITLE, SETTINGS, DATA_LORE, DIFFICULTY_SELECTION, GAMEPLAY, ENDING } GameScreen;
typedef enum SettingsScreen { GRAPHICS = 0, AUDIO, DISPLAY, CUSTOM } SettingsScreen;
typedef enum SettingState { LOW = 0, MID, HI} SettingState;
typedef enum DataScreen { TUTORIALS, RECOVERED } DataScreen;
typedef enum MiniGameTutorial {BALL, CONNECTING, FINDER, TYPE} MiniGameTutorial;

// Deklaracja zmiennych globalnych
extern GameScreen currentScreen;
extern SettingState debugMode;
extern SettingsScreen currentSettings;
extern DataScreen currentDataScreen;
extern MiniGameTutorial currentTutorial;
extern MiniGameManager gameManager;
extern Texture2D botnetTexture;
extern Texture2D ddosTexture;
extern Texture2D mailbombTexture;
extern Rectangle screen;
extern char command[100];
extern int letterCount;
extern bool mouseOnText;
extern int framesCounter;
extern int backTimer;
extern std::string input;
extern const int screenWidth;
extern const int screenHeight;
extern std::string history[50];
extern std::string historyDrawn[50];
extern int upTimes;
extern bool exitGame;
extern Vector2 mousePos;
extern Font alagard;
extern Font pixeled;
extern std::mt19937 rng;
extern std::string assetsPath;
extern std::string configPath;
extern Rectangle TextureKernel;
extern Color primaryColor;

extern Model model_globe;
extern Model model_cog;
extern Model model_data;
extern Model model_door;
extern Camera camera;

//Title
extern Rectangle button_play;
extern Rectangle button_lore;
extern Rectangle button_settings;
extern Rectangle button_exit;
extern Rectangle title;
extern Rectangle desc_window;
extern Rectangle anim_window_title;
extern RenderTexture2D space3d;

// Settings
extern float general_volume;
extern float effects_volume;

// Difficulty
extern int SelectedDifficulty;

// Music
extern Music main_theme;
extern bool mute_audio;
extern TraceLogCallback failed_to_load_music;

extern GameplayManager gameplayManager;

#endif // GLOBALS_H

// Funcs
void DrawTextB(const char *text, float posX, float posY, int fontSize, Color color);
void DrawTextC(const char *text, float posX, float posY, int fontSize, Color color);
float ShakeXY(float pos, float intensity);
Rectangle ShakeRectangle(Rectangle rec, float intensity);
Rectangle ShakeRectangleOnClick(Rectangle rec, float intensity);
void ProjectModel(const char* objFilePath, Color modelColor, Rectangle destRect);
float Clamp(float value, float min, float max);
float Enround(float num, int pos);
std::string getSubfolderPath(std::string subfolder);

