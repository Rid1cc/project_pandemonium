#include "gameplay_draw.h"
#include "gamescreen.h"

//Tutaj głowny ekran gry, razem z terminalem itp

void DrawGameplay(Rectangle textBox, const char* name, int letterCount, bool mouseOnText, int framesCounter) {
    ClearBackground(RAYWHITE);

    DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

    if (mouseOnText) {
        if (letterCount < MAX_INPUT_CHARS) {
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        } else {
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
        }
    }
}
