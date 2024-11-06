#include "gameplay_draw.h"
#include "globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne

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
    DrawText(command, 65, screenHeight-50, 20, ORANGE);
    if (letterCount < 99 && ((framesCounter / 20) % 2) == 0) {
        DrawText("_", 65 + 4 + MeasureText(command, 20), screenHeight-50, 20, ORANGE);
    }
}
