#include "./headers/MiniGame.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : window({x, y, width, height}), title(title), gameComplete(false), isOpen(true), isActive(false) {}

// Base Update method (can be overridden)
void MiniGame::Update() {
    Vector2 mousePosition = GetMousePosition();
}

// Base Draw method (can be overridden)
void MiniGame::Draw() {
    DrawWindow();
}

// Draw the popup window
void MiniGame::DrawWindow() {
    DrawRectangleRec(window, BLACK);
    if (!isActive) DrawRectangleLinesEx(window, 2, ORANGE);
    else if (isActive) DrawRectangleLinesEx(window, 2, Color {0,94,255,255});
    DrawText(title.c_str(), window.x + 10, window.y + 10, 20, WHITE);
    DrawText("X", window.x + window.width - 15, window.y + 5, 20, RED);
}


void MiniGame::Close() {
    isOpen = false;
}