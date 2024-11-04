#include "gameplay_update.h"
#include "globals.h"  // Zmienne globalne są dostępne tutaj
#include <chrono>
#include <thread>
#include <string>



void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string history) {
    // Implementacja funkcji UpdateGameplay
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = true;
    
    int key = GetCharPressed();
    

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letterCount < 99)) {
            command[letterCount] = (char)key;
            command[letterCount + 1] = '\0';
            letterCount++;
        }
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_ENTER)){
        history = command;
        for(int i=0;i<=100;i++)
        {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        command[i] = '\0';
        }
    }

    //backspace
    if (IsKeyPressed(KEY_BACKSPACE)) {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        command[letterCount] = '\0';
    } 

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
}
