#include "headers/gameplay_draw.h"
#include "headers/globals.h"  // Wczytanie zmiennych globalnych, jeśli są potrzebne
#include <string>



// Forward declarations of helper functions
void DrawMonitor();
void DrawLabels();
// Gampeplay windows
//===========
void DrawTerminal();
void DrawPIDMenu();
void DrawInfoPanel();
void DrawAttackMenu();
void DrawHealthBar();
//===========
void DrawTerminalInput(const char* command, int letterCount, int framesCounter, bool mouseOnText);
void DrawTerminalOutput(const std::string* historyDrawn, int historySize);
void DrawVersionInfo();
void DrawGameManager();

void DrawGameplay(Rectangle textBox, const char* command, int letterCount, bool mouseOnText, int framesCounter, std::string* historyDrawn) {
    ClearBackground(BLACK);
    DrawMonitor();
    DrawLabels();
    //display main gameplay
    //=============
    DrawVersionInfo();
    DrawTerminal();
    DrawPIDMenu();
    DrawInfoPanel();
    DrawAttackMenu();
    DrawHealthBar();
    //=============
    DrawTerminalInput(command, letterCount, framesCounter, mouseOnText);
    DrawTerminalOutput(historyDrawn, 15);
    DrawGameManager();
}

void DrawMonitor() {
    // Monitor border
    DrawRectangleLinesEx(screen, 3.0f, ORANGE);
}

void DrawLabels() {
    //Terminal
    
    //InfoPanel

    //StatusWindow

    //AttackMenu

    //HealthBar
}

void DrawHealthBar() {
    DrawRectangle(healthBar.x, healthBar.y, healthBar.width, healthBar.height, ORANGE);
    DrawRectangleLinesEx(healthBar, 1, GRAY);
}

void DrawAttackMenu() {
    DrawRectangleLinesEx(attackMenu, 2, ORANGE);

    // icon 1
    DrawRectangle(attackMenu.x + 20, attackMenu.y + 25, 56, 56, ORANGE);
    // icon 2
    DrawRectangle(attackMenu.x + 96, attackMenu.y + 25, 56, 56, ORANGE);
    // icon 1
    DrawRectangle(attackMenu.x + 172, attackMenu.y + 25, 56, 56, ORANGE);
}

void DrawInfoPanel() {
    DrawRectangleLinesEx(infoPanel, 2, ORANGE);
}

void DrawTerminal() {
    DrawRectangleLinesEx(terminalWindow, 2, ORANGE);
    // DrawRectangleLinesEx(textBox, 2, ORANGE);
}

void DrawPIDMenu() {
    DrawRectangleLinesEx(PIDMenu, 2, ORANGE);
}






void DrawLines() {
    // Horizontal Lines
    float halfHeight = static_cast<float>(screenHeight) / 2;
    DrawLineEx({50, halfHeight + 5}, {static_cast<float>(screenWidth) - 350, halfHeight + 5}, 3, GREEN);
    DrawLineEx({50, halfHeight - 5}, {static_cast<float>(screenWidth) - 350, halfHeight - 5}, 3, BLUE);

    // Vertical Lines
    DrawLineEx({static_cast<float>(screenWidth) - 350, 25}, {static_cast<float>(screenWidth) - 350, halfHeight - 5}, 3, ORANGE);
    DrawLineEx({static_cast<float>(screenWidth) - 350, halfHeight + 5}, {static_cast<float>(screenWidth) - 350, static_cast<float>(screenHeight) - 25}, 3, PURPLE);
    DrawLineEx({static_cast<float>(screenWidth) - 340, 25}, {static_cast<float>(screenWidth) - 340, static_cast<float>(screenHeight) - 25}, 3, YELLOW);
}

void DrawVersionInfo() {
    // System Information
    DrawTextC("ParadisiOS ver 7.3, up to date.", 5, 2, 12, WHITE);
}

void DrawTerminalInput(const char* command, int letterCount, int framesCounter, bool mouseOnText) {
    // Terminal Input Prompt
    int terminalY = terminalWindow.y + terminalWindow.height - 25;
    // DrawText(">", 55, terminalY, 20, ORANGE);
    DrawText(">", terminalWindow.x + 5, terminalWindow.y + terminalWindow.height - 25, 20, ORANGE);
    // DrawTextB(command, 65, terminalY, 20, ORANGE);
    DrawTextB(command, terminalWindow.x + 5, terminalWindow.y + terminalWindow.height - 25, 20, ORANGE);

    // Blinking Cursor
    if (letterCount < 40 && ((framesCounter / 20) % 2) == 0) {
        float textWidth = MeasureTextEx(alagard, command, 20, 2).x;
        DrawTextB("_", 69 + static_cast<int>(textWidth), terminalY, 20, ORANGE);
    }
}

void DrawTerminalOutput(const std::string* historyDrawn, int historySize) {
    // Terminal Output History
    int baseY = GetScreenHeight() - 70;
    for(int i = 0; i < historySize; i++) {
        DrawTextB(historyDrawn[i].c_str(), 55, baseY - (i * 20), 20, ORANGE);
    }
}

void DrawGameManager() {
    // Draw additional game elements managed by gameManager
    gameManager.Draw();
}
