#ifndef GAMEPLAY_UPDATE_H
#define GAMEPLAY_UPDATE_H

#include "raylib.h"       // Dołączenie raylib.h zapewnia dostęp do definicji typu Rectangle
#include "gamescreen.h"   // Dołączenie gamescreen.h zapewnia dostęp do definicji GameScreen

void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* name, int& letterCount, bool& mouseOnText, int& framesCounter);

#endif // GAMEPLAY_UPDATE_H
