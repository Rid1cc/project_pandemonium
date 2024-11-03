#ifndef GAMEPLAY_UPDATE_H
#define GAMEPLAY_UPDATE_H

#include "raylib.h"       // Dołączenie raylib.h zapewnia dostęp do definicji typu Rectangle
#include "globals.h"


void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter);

#endif // GAMEPLAY_UPDATE_H
