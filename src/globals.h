#ifndef GLOBALS_H
#define GLOBALS_H
#include "raylib.h"       // Dołączenie, aby uzyskać dostęp do Rectangle

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

// Deklaracja zmiennych globalnych
extern GameScreen currentScreen;
extern Rectangle textBox;
extern char command[100];
extern int letterCount;
extern bool mouseOnText;
extern int framesCounter;
extern const int screenWidth;
extern const int screenHeight;

#endif // GLOBALS_H
