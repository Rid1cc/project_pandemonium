#include "gameplay_update.h"
#include "globals.h"  
#include "command_interpreter.h"  // Dodajemy nagłówek interpretera
#include <string>
#include <iostream>

void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string* history, int& upTimes) {
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;
    
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
        upTimes = 0;

        // Przechowujemy wprowadzone polecenie w historii
        for(int i = 29; i > 0; i--) {
            history[i] = history[i - 1];
        }
        history[0] = command;

        // Wywołujemy executeCommand z bieżącą komendą
        executeCommand(command);

        // Czyścimy aktualne polecenie
        for(int i = 0; i <= 100; i++) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            command[i] = '\0';
        }
    }

    // Obsługa strzałki w górę/dół i backspace (pozostała logika)
    if (IsKeyPressed(KEY_BACKSPACE)) {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        command[letterCount] = '\0';
    }

    if (IsKeyDown(KEY_BACKSPACE)) {
        if (backTimer >= 30) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            command[letterCount] = '\0';
        }
        else {
            backTimer++;
        }
    } else {
        backTimer = 0;
    }

        // Obsługa strzałki w górę - przeglądanie historii do tyłu
    if (IsKeyPressed(KEY_UP)) {
        if (upTimes < 29 && !history[upTimes].empty()) {
            std::string previousCommand = history[upTimes];
            letterCount = previousCommand.length();
            upTimes++;
            // Przepisz wartość poprzedniego polecenia do `command`
            std::copy(previousCommand.begin(), previousCommand.end(), command);
            command[letterCount] = '\0';  // Dodaj zakończenie do `command`
        }
    }

    // Obsługa strzałki w dół - przeglądanie historii do przodu
    if (IsKeyPressed(KEY_DOWN)) {
        if (upTimes > 0) {
            upTimes--;  // Przejdź do nowszego polecenia
            std::string nextCommand = history[upTimes-1];
            letterCount = nextCommand.length();

            // Przepisz wartość nowszego polecenia do `command`
            std::copy(nextCommand.begin(), nextCommand.end(), command);
            command[letterCount] = '\0';  // Dodaj zakończenie do `command`
        } else if (upTimes == 0) {
            // Jeśli doszliśmy do `upTimes == 0`, wracamy do pustego pola
            letterCount = 0;
            command[0] = '\0';  // Ustawiamy `command` na pusty string
        }
    }


    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    if (IsKeyPressed(KEY_ESCAPE)) currentScreen = TITLE;
}
