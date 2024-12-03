#include "./headers/MiniGameManager.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : window({x, y, width, height}), title(title), isDragable(false), isOpen(true) {}

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
    if (isDragable) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            window.x = mousePosition.x - dragOffset.x;
            window.y = mousePosition.y - dragOffset.y;
        } else {
            isDragable = false;
        }
    } else if (CheckCollisionPointRec(GetMousePosition(), {window.x, window.y, window.width, 30}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isDragable = true;
        Vector2 mousePosition = GetMousePosition();
        dragOffset = {mousePosition.x - window.x, mousePosition.y - window.y};
    }
}

// Draw the popup window
void MiniGame::DrawWindow() {
    DrawRectangleRec(window, BLACK);                    // Background
    DrawRectangleLinesEx(window, 2, ORANGE);            // Border
    DrawText(title.c_str(), window.x + 10, window.y + 10, 20, WHITE); // Title
    if (CheckCollisionPointRec(GetMousePosition(), {window.x + window.width - 20, window.y, 20, 20}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Close(); // Close button clicked
    }
    DrawText("X", window.x + window.width - 15, window.y + 5, 20, RED); // Close button
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
