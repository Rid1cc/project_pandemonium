#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"     
#include <string>

typedef enum GameScreen { LOGO = 0, TITLE, SETTINGS, GAMEPLAY, ENDING } GameScreen;

// Deklaracja zmiennych globalnych
extern GameScreen currentScreen;
extern Rectangle textBox;
extern char command[100];
extern int letterCount;
extern bool mouseOnText;
extern int framesCounter;
extern int backTimer;
extern std::string input;
extern const int screenWidth;
extern const int screenHeight;
extern std::string history[30];
extern std::string historyDrawn[30];
extern int upTimes;
extern Font alagard;
void DrawTextB(const char *text, float posX, float posY, int fontSize, Color color);

// Settings
extern float general_volume;
extern float effects_volume;

// Music
extern Music main_theme;
extern bool mute_audio;
extern TraceLogCallback failed_to_load_music;
#endif // GLOBALS_H
