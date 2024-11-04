#include "gameplay_update.h"
#include "globals.h"  // Zmienne globalne są dostępne tutaj




void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer) {
    // Implementacja funkcji UpdateGameplay
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = true;
    
    int key = GetCharPressed();
    char* history[100][10];

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letterCount < 99)) {
            command[letterCount] = (char)key;
            command[letterCount + 1] = '\0';
            letterCount++;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER)){
        history[0][0] = command;
        command = 0;
    }

    //backspace
    if (IsKeyPressed(KEY_BACKSPACE)) {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        command[letterCount] = '\0';
    } 

    //po 30 klatkach usuwa duzo 
    if (IsKeyDown(KEY_BACKSPACE)){
        if(backTimer>=30){
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            command[letterCount] = '\0';
        }
        else{
        backTimer++;
        }
    }else{
        backTimer=0;
    }

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
}
