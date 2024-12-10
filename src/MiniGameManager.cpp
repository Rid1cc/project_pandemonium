#include "./headers/MiniGameManager.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : window({x, y, width, height}), title(title), isDragable(false), isOpen(true) {}


// Base Update method (can be overridden)
void MiniGame::Update() {
        Vector2 mousePosition = GetMousePosition();
        HandleDrag(mousePosition); // Handle drag functionality
}

// Base Draw method (can be overridden)
void MiniGame::Draw() {
    DrawWindow(); // Draw the popup window
}

// Handle dragging of the window
void MiniGame::HandleDrag(Vector2 mousePosition) {
    if (isDragable) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            window.x = mousePosition.x - dragOffset.x;
            window.y = mousePosition.y - dragOffset.y;
        } else {
            isDragable = false;
            StopDragging();
        }
    } else if (CheckCollisionPointRec(mousePosition, {window.x, window.y, window.width, 30}) && 
               IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBeDragged(mousePosition)) {
        manager->BringToFront(GetThis());
        isOnTop = true;
        isDragable = true;
        //PushToFront();
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
    } else if (gameComplete) {
        Close();
    }
    DrawText("X", window.x + window.width - 15, window.y + 5, 20, RED); // Close button
}

// Close the window
void MiniGame::Close() {
    isOpen = false;
}

bool MiniGame::CanBeDragged(Vector2 mousePosition) {
    if (!manager->currentlyDragged && CheckCollisionPointRec(mousePosition, {window.x, window.y, window.width, window.height})){
        manager->currentlyDragged = GetThis();
        return true;
    }
    return false;
    
}

void MiniGame::StopDragging() {
    manager->currentlyDragged.reset();
    //isOnTop = false;
}

// Is the window open?
bool MiniGame::IsOpen() const {
    return isOpen;
}



// Add a game to the manager
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game) {
    game->SetManager(this);
    games.push_back(game);
    onTop = game;
}

// Update all active games
void MiniGameManager::Update() {
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
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

void MiniGameManager::BringToFront(std::shared_ptr<MiniGame> game) {
    auto it = std::find(games.begin(), games.end(), game);
    if (it != games.end()) {
        games.erase(it);
        games.push_back(game);
        onTop = game;
    }
}
