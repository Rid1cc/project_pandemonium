#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"     
#include <string>

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;


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
extern int upTimes;
extern Font alagard;
void DrawTextB(const char *text, float posX, float posY, int fontSize, Color color);

#endif // GLOBALS_H
