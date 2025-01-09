#ifndef TYPE_GAME_H
#define TYPE_GAME_H

#include "../headers/MiniGameManager.h"
#include "../headers/globals.h"
#include <sstream>
#include <iostream>
#include <mutex>

class TypeGame: public MiniGame {
private:
    std::vector<std::string> text; // texts to display
    std::string randomText; // drawn text
    
    std::string typedText; 

    std::vector<bool> correctness;
    bool allCorrect;

    int textFontSize = 35;
    bool isCursorVisible;
    int cursorX = 0;
    int cursorY = 0;
    int currentNumber; // current text[] number 
    float cursorBlinkTime = 0.5f;
    float timeSinceLastCursorBlink = 0.0f;
    bool isTyping;
    int randomTextLength;
    
    void UpdateCorrectness();
    void UpdateCurrentNumber(); // update cuurent text[] number
    void DrawRandomText(); // draw drawn text
    void DrawCursor(); // draw cursor 
    void UpdateCursor(float deltaTime); // cursor blinking and position
    void DrawTypedText(); // draw typed letters red or green
    void UpdateTypedText();
    bool AllCorrect();
    void shakeWindow(float intensity, float duration);
    std::mutex inputMutex; // Added mutex for thread safety

public:
    TypeGame(float x, float y, float width, float height, const std::string& title);

    bool isTypeWin; // WIN OR LOSE

    ~TypeGame(); // Ensure destructor is declared

    void Update() override;
    void Draw() override;
};

#endif