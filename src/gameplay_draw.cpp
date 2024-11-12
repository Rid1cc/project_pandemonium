#include "headers/gameplay_draw.h"
#include "headers/globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne

void DrawGameplay(Rectangle textBox, const char* command, int letterCount, bool mouseOnText, int framesCounter) {
    ClearBackground(BLACK);

    //Monitor
    DrawRectangleLines(50, 25, screenWidth-100, screenHeight-50, ORANGE);

    //Horizontal lines
    DrawLine(50, (screenHeight/2)+5, screenWidth-350, (screenHeight/2)+5, ORANGE);  
    DrawLine(50, (screenHeight/2)-5, screenWidth-350, (screenHeight/2)-5, ORANGE);

    //Vertical lines
    DrawLine(screenWidth-350, 25, screenWidth-350, (screenHeight/2)-5, ORANGE);
    DrawLine(screenWidth-350, (screenHeight/2)+5, screenWidth-350, screenHeight-25, ORANGE);
    DrawLine(screenWidth-340, 25, screenWidth-340, screenHeight-25, ORANGE);

    //Input
    DrawText(">", 55, screenHeight-50, 20, ORANGE);
    DrawTextB(command, 65, screenHeight-50, 20, ORANGE);
    if (letterCount < 99 && ((framesCounter / 20) % 2) == 0) {
        //Draw "_" if frames/20%2=0 (blinking) - measure text with exact spacing for the font.
        DrawText("_", 65 + 4 + MeasureTextEx(alagard, command, 20, 2).x, screenHeight-50, 20, ORANGE);
    }

    //Output
}
