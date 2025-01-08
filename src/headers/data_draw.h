#ifndef DATA_DRAW_H
#define DATA_DRAW_H

#include "globals.h"
#include "raylib.h"

extern Rectangle button_tutorials;
extern Rectangle button_recovered;
extern Rectangle button_BallGame;
extern Rectangle button_ConnectingGame;
extern Rectangle button_FinderGame;
extern Rectangle button_TypeGame;

void DrawData();
void DataButton(Rectangle rect, const char* text, Color color, int FontSize, bool isMouseOnButton, int xPos);
void DrawTutorials();
void DrawTutorialDescription(Rectangle rect, int FontSize, std::string text, Color color);
void DrawRecovered();

#endif