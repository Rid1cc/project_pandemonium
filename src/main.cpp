#include "raylib.h"
#include "gameplay_update.h"
#include "gameplay_draw.h"
#include "globals.h"
#include "command_interpreter.h"


int main(void) {

    InitWindow(screenWidth, screenHeight, "Pandemonium");

    SetExitKey(0); // ESCAPE NO LONGER CLOSES THE GAME!

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case LOGO: {
                framesCounter++;
                if (framesCounter > 120) currentScreen = TITLE;
            } break;
            case TITLE: {
                if (IsKeyPressed(KEY_ENTER)) currentScreen = GAMEPLAY;
            } break;
            case GAMEPLAY: {
                UpdateGameplay(currentScreen, textBox, command, letterCount, mouseOnText, framesCounter, backTimer, history, upTimes);
            } break;
            case ENDING: {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)) currentScreen = TITLE;
            } break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen) {
            case LOGO: {
                DrawText("UnderSmoked Studios", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case TITLE: {
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
            } break;
            case GAMEPLAY: {
                DrawGameplay(textBox, command, letterCount, mouseOnText, framesCounter);
            } break;
            case ENDING: {
                DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
            } break;
            default: break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
