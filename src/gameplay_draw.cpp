#include "gameplay_draw.h"
#include "globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne

void DrawGameplay(Rectangle textBox, const char* name, int letterCount, bool mouseOnText, int framesCounter) {
    // Implementacja funkcji
    ClearBackground(RAYWHITE);
    DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 9), 315, 250, 20, DARKGRAY);

    if (mouseOnText && letterCount < 9 && ((framesCounter / 20) % 2) == 0) {
        DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
    }
}
