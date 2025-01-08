#ifndef DATA_DRAW_H
#define DATA_DRAW_H

#include "globals.h"
#include "raylib.h"
#include "DifficultySelector.h"

extern Rectangle button_tutorials;
extern Rectangle button_recovered;
extern Rectangle button_BallGame;
extern Rectangle button_ConnectingGame;
extern Rectangle button_FinderGame;
extern Rectangle button_TypeGame;
extern Rectangle button_recovered1;
extern Rectangle button_recovered2;
extern Rectangle button_recovered3;

void DrawData();
void DataButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton, int xPos);
void DrawTutorials();
void DrawTutorialDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawRecovered();
void DrawBlockedRecoveredButton(Rectangle rect, const char* text, int FontSize, bool isMouseOnButton, int xPos);
#endif