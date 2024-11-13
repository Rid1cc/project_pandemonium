#include "headers/gameplay_draw.h"
#include "headers/globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne
#include <string>

void DrawGameplay(Rectangle textBox, const char* command, int letterCount, bool mouseOnText, int framesCounter, std::string* historyDrawn) {
    ClearBackground(BLACK);

    //Monitor
    DrawRectangleLines(50, 25, GetScreenWidth()-100, GetScreenHeight()-50, ORANGE);

    //Horizontal lines
    DrawLine(50, (GetScreenHeight()/2)+5, GetScreenWidth()-350, (GetScreenHeight()/2)+5, ORANGE);  
    DrawLine(50, (GetScreenHeight()/2)-5, GetScreenWidth()-350, (GetScreenHeight()/2)-5, ORANGE);

    //Vertical lines
    DrawLine(GetScreenWidth()-350, 25, GetScreenWidth()-350, (GetScreenHeight()/2)-5, ORANGE);
    DrawLine(GetScreenWidth()-350, (GetScreenHeight()/2)+5, GetScreenWidth()-350, GetScreenHeight()-25, ORANGE);
    DrawLine(GetScreenWidth()-340, 25, GetScreenWidth()-340, GetScreenHeight()-25, ORANGE);

    //Terminal Input
    DrawText(">", 55, GetScreenHeight()-50, 20, ORANGE);
    DrawText(command, 65, GetScreenHeight()-50, 20, ORANGE);
    if (letterCount < 99 && ((framesCounter / 20) % 2) == 0) {
        //Draw "_" if frames/20%2=0 (blinking) - measure text with exact spacing for the font.
        DrawText("_", 65 + 4 + MeasureTextEx(alagard, command, 20, 2).x, GetScreenHeight()-50, 20, ORANGE);
    }

    //Terminal Output
    for(int i = 0; i<15; i++){
        DrawTextB(historyDrawn[i].c_str(), 55, GetScreenHeight()-70-(i*20), 20, ORANGE);
    }
    
}
