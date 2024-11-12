#ifndef GAMEPLAY_DRAW_H
#define GAMEPLAY_DRAW_H

#include "raylib.h"
#include "globals.h"


void DrawGameplay(Rectangle textBox, const char* name, int letterCount, bool mouseOnText, int framesCounter, std::string* historyDrawn);

#endif // GAMEPLAY_DRAW_H
