#include "headers/title_draw.h"


void DrawTitle() {
    // drawing backgrounds
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    // drawing the line 
    DrawLine(GetScreenWidth()/4, GetScreenHeight()/4, GetScreenWidth()/4, GetScreenHeight()/4 + 200, ORANGE);

    //drawing texts
    DrawText("TITLE SCREEN", 20, 20, 40, ORANGE);
    DrawText("PRESS ENTER to go to GAMEPLAY SCREEN", GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 10, 20, ORANGE);
    DrawText("PRESS S to go to SETTINGS SCREEN", GetScreenWidth()/4 + 10, GetScreenHeight()/4 + 40, 20, ORANGE);
}
