#include "MinigraLitwa1.h"

AxeGame::AxeGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), rotation(0) {}

void AxeGame::Update() {
    MiniGame::Update(); // Handle dragging

    // Dynamically calculate rectangle position relative to popup position
    Vector2 popupPos = {window.x, window.y}; // Assume popupX and popupY are accessible
    rectInner = {popupPos.x + window.width / 4, popupPos.y + window.height / 4, window.width / 2, window.height / 2};
}


void AxeGame::Draw() {
    MiniGame::Draw(); // Draw window
    DrawCircle(int screenWidth/2 , {rectInner.w, rectInner.height / 2}, rotation, ORANGE);
}
