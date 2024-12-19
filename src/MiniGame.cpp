#include "./headers/MiniGame.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : window({x, y, width, height}), title(title), gameComplete(false), isOpen(true) {}

// Base Update method (can be overridden)
void MiniGame::Update() {
}

// Base Draw method (can be overridden)
void MiniGame::Draw() {
}

void MiniGame::Close() {
    isOpen = false;
}