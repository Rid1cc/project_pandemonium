#include "headers/gameplay_update.h"
#include "headers/globals.h"  
#include "headers/CommandInterpreter.h" 
#include <string>
#include <iostream>
#include <algorithm> // For std::copy
#include "headers/MiniGameManager.h"

// Function Declarations
void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string* history, int& upTimes);
bool IsMouseOnTextBox(const Rectangle& textBox);
void CaptureTextInput(char* command, int& letterCount);
void ExecuteCommand(CommandInterpreter& cmdInterpreter, char* command, std::string* history, int& upTimes);
void UpdateHistory(std::string* history, const char* command);
void ClearCommand(char* command, int& letterCount);
void HandleBackspace(char* command, int& letterCount, int& backTimer);
void NavigateHistory(char* command, int& letterCount, std::string* history, int& upTimes, bool isUp);
void UpdateCursorState(bool mouseOnText, int& framesCounter);
void HandleEscapeKey(GameScreen& currentScreen);

// Function Definitions
void UpdateGameplay(GameScreen& currentScreen, Rectangle& textBox, char* command, int& letterCount, bool& mouseOnText, int& framesCounter, int& backTimer, std::string* history, int& upTimes) {
    // Update mouse state
    mouseOnText = IsMouseOnTextBox(textBox);

    // Handle text input
    CaptureTextInput(command, letterCount);

    // Initialize Command Interpreter
    static CommandInterpreter cmdInterpreter;

    // Handle command execution on Enter key press
    if (IsKeyPressed(KEY_ENTER)) {
        upTimes = 0;
        ExecuteCommand(cmdInterpreter, command, history, upTimes);
    }

    // Handle backspace logic
    HandleBackspace(command, letterCount, backTimer);

    // Handle history navigation
    if (IsKeyPressed(KEY_UP)) {
        NavigateHistory(command, letterCount, history, upTimes, true);
    }
    if (IsKeyPressed(KEY_DOWN)) {
        NavigateHistory(command, letterCount, history, upTimes, false);
    }

    // Update cursor and frame counter
    UpdateCursorState(mouseOnText, framesCounter);

    // Update game manager
    gameManager.Update();

    // Handle escape key to return to title screen
    HandleEscapeKey(currentScreen);
}


bool IsMouseOnTextBox(const Rectangle& textBox) {
    return CheckCollisionPointRec(GetMousePosition(), textBox);
}

void CaptureTextInput(char* command, int& letterCount) {
    int key = GetCharPressed();
    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letterCount < 99)) {
            command[letterCount] = static_cast<char>(key);
            command[letterCount + 1] = '\0';
            letterCount++;
        }
        key = GetCharPressed();
    }
}

void UpdateHistory(std::string* history, const char* command) {
    // Shift history buffer
    for(int i = 29; i > 0; --i) {
        history[i] = history[i - 1];
    }
    history[0] = std::string(command);
}

void ExecuteCommand(CommandInterpreter& cmdInterpreter, char* command, std::string* history, int& upTimes) {
    // Update history
    UpdateHistory(history, command);

    // Execute the command
    cmdInterpreter.executeCommand(command);

    // Clear the command input
    ClearCommand(command, upTimes);
}

void ClearCommand(char* command, int& letterCount) {
    for(int i = 0; i <= 100; ++i) {
        if (letterCount > 0) letterCount--;
        command[i] = '\0';
    }
    letterCount = 0;
}

void HandleBackspace(char* command, int& letterCount, int& backTimer) {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (letterCount > 0) {
            letterCount--;
            command[letterCount] = '\0';
        }
    }

    if (IsKeyDown(KEY_BACKSPACE)) {
        if (backTimer >= 30) {
            if (letterCount > 0) {
                letterCount--;
                command[letterCount] = '\0';
            }
        } else {
            backTimer++;
        }
    } else {
        backTimer = 0;
    }
}

void NavigateHistory(char* command, int& letterCount, std::string* history, int& upTimes, bool isUp) {
    if (isUp) {
        if (upTimes < 29 && !history[upTimes].empty()) {
            std::string previousCommand = history[upTimes];
            letterCount = previousCommand.length();
            upTimes++;
            std::copy(previousCommand.begin(), previousCommand.end(), command);
            command[letterCount] = '\0'; 
        }
    } else {
        if (upTimes > 0) {
            upTimes--;
            std::string nextCommand = history[upTimes - 1];
            letterCount = nextCommand.length();
            std::copy(nextCommand.begin(), nextCommand.end(), command);
            command[letterCount] = '\0';
        } else if (upTimes == 0) {
            ClearCommand(command, letterCount);
        }
    }
}

void UpdateCursorState(bool mouseOnText, int& framesCounter) {
    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        framesCounter++;
        if(framesCounter >= 60){
            framesCounter = 0;
        }
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        framesCounter = 0;
    }
}

void HandleEscapeKey(GameScreen& currentScreen) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentScreen = TITLE;
    }
}
