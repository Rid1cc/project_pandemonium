#ifndef GLOBALS_H
#define GLOBALS_H

#include "gamescreen.h"   // Definicja GameScreen musi być wczytana jako pierwsza
#include "raylib.h"       // Dołączenie, aby uzyskać dostęp do Rectangle

// Deklaracja zmiennych globalnych
extern GameScreen currentScreen;
extern Rectangle textBox;
extern char name[10];
extern int letterCount;
extern bool mouseOnText;
extern int framesCounter;

#endif // GLOBALS_H
