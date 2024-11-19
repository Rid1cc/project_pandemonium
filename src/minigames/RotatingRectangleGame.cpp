#include "RotatingRectangleGame.h"

RotatingRectangleGame::RotatingRectangleGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), rotation(0) {
}

void RotatingRectangleGame::Update() {
    MiniGame::Update(); // Handle dragging

    // Dynamically calculate rectangle position relative to popup position
    Vector2 popupPos = {window.x, window.y}; // Assume popupX and popupY are accessible
    rectInner = {popupPos.x + window.width / 4, popupPos.y + window.height / 4, window.width / 2, window.height / 2};

    rotation += 2.0f;   // Rotate rectangle
    if (rotation >= 360.0f) rotation = 0.0f;
}


void RotatingRectangleGame::Draw() {
    MiniGame::Draw(); // Draw window
    DrawRectanglePro(rectInner, {rectInner.width / 2, rectInner.height / 2}, rotation, ORANGE);
}
