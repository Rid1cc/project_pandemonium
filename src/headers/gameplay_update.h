#ifndef GAMEPLAY_UPDATE_H
#define GAMEPLAY_UPDATE_H

#include "raylib.h" 
#include "globals.h"
#include <string>


void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string* history, int& upTimes);

#endif // GAMEPLAY_UPDATE_H
