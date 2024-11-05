#include "gameplay_update.h"
#include "globals.h"  // Zmienne globalne są dostępne tutaj
#include <string>
#include <iostream>



void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string* history, int& upTimes) {
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
        //zresetuj licznik ups & downs
        upTimes = 0;

        //historia dziala do 29 linijek wstecz

        //nadpisujemy schodkowo historie
        for(int i=29;i>0;i--){
            history[i] = history[i-1];
        }
        //aplikujemy najnowszą linijkę historii
        history[0] = command;

        //wywalamy aktualną linijkę kodu
        for(int i=0;i<=100;i++)
        {
        letterCount--;
        if (letterCount < 0) letterCount = 0;
        command[i] = '\0';
        }

        //check czy dziala
        for(int i = 5; i>-1; i--){
            std::cout << history[i] << std::endl;
        }
        
    }

    // Strzalka w gore
    if (IsKeyPressed(KEY_UP)) {
        if (upTimes < 29 && !history[upTimes].empty()) {
              // Przejdź do starszego polecenia
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
