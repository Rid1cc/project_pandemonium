#include "./headers/MiniGameManager.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : rect({x, y, width, height}), title(title), isDragging(false), isOpen(true) {}

// Base Update method (can be overridden)
void MiniGame::Update() {
    HandleDrag(); // Handle drag functionality
}

// Base Draw method (can be overridden)
void MiniGame::Draw() {
    DrawWindow(); // Draw the popup window
}

// Handle dragging of the window
void MiniGame::HandleDrag() {
    if (isDragging) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            rect.x = mousePosition.x - dragOffset.x;
            rect.y = mousePosition.y - dragOffset.y;
        } else {
            isDragging = false;
        }
    } else if (CheckCollisionPointRec(GetMousePosition(), rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isDragging = true;
        Vector2 mousePosition = GetMousePosition();
        dragOffset = {mousePosition.x - rect.x, mousePosition.y - rect.y};
    }
}

// Draw the popup window
void MiniGame::DrawWindow() {
    DrawRectangleRec(rect, BLACK);                    // Background
    DrawRectangleLinesEx(rect, 2, ORANGE);            // Border
    DrawText(title.c_str(), rect.x + 10, rect.y + 10, 20, WHITE); // Title
    if (CheckCollisionPointRec(GetMousePosition(), {rect.x + rect.width - 20, rect.y, 20, 20}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Close(); // Close button clicked
    }
    DrawText("X", rect.x + rect.width - 15, rect.y + 5, 20, RED); // Close button
}

// Close the window
void MiniGame::Close() {
    isOpen = false;
}

// Is the window open?
bool MiniGame::IsOpen() const {
    return isOpen;
}

// Add a game to the manager
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game) {
    games.push_back(game);
}

// Update all active games
void MiniGameManager::Update() {
    for (auto& game : games) {
        if (game->IsOpen()) {
            game->Update();
        }
    }
}

// Draw all active games
void MiniGameManager::Draw() {
    for (auto& game : games) {
        if (game->IsOpen()) {
            game->Draw();
        }
    }
}
