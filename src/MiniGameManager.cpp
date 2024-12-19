#include "./headers/MiniGameManager.h"

// Add a game to the manager
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game) {
    games.push_back(game);
}

// Update all activeGame games
void MiniGameManager::Update() {
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DragWindow(game, GetMousePosition());
            if (IsWindowFirst(game)) {
                game->Update();
            }
        }
        // Close game
        if ((CheckCollisionPointRec(GetMousePosition(), {game->window.x + game->window.width - 20, game->window.y, 20, 20}) &&
             IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBeInteracted(game, GetMousePosition())) || game->gameComplete) {
            Close(game);
        }
    }
}

//Draw All games
void MiniGameManager::Draw() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DrawRectangleRec(game->window, BLACK);
            if (!IsWindowFirst(game)) DrawRectangleLinesEx(game->window, 2, ORANGE);
            else DrawRectangleLinesEx(game->window, 2, Color {0,94,255,255});
            //DrawRectangleLinesEx(window, 2, ORANGE);
            DrawText(game->title.c_str(), game->window.x + 10, game->window.y + 10, 20, WHITE);
            DrawText("x", game->window.x + game->window.width - 15, game->window.y + 5, 20, RED);
            game->Draw();
        }
    }
}


void MiniGameManager::SetWindowFirst(std::shared_ptr<MiniGame>&game) {
    auto it = std::find(games.begin(), games.end(), game);
    if (it != games.end() && !CheckCollisionPointRec(GetMousePosition(), games.back()->window)) {
        std::iter_swap(it, games.end() - 1);
    }
}

bool MiniGameManager::CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition) {
    if (game == games.back() && CheckCollisionPointRec(mousePosition, game->window)) 
        return true;
    return false;
}

bool MiniGameManager::IsWindowFirst(std::shared_ptr<MiniGame>& game) {
    if (game == games.back())
        return true;
    return false;
}

void MiniGameManager::DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition) {
    if (game->isDragable) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsWindowFirst(game)) {
            Vector2 mouseDelta = GetMouseDelta();
            game->window.x += mouseDelta.x;
            game->window.y += mouseDelta.y;
        } else {
            StopDragging(game);
            game->isDragable = false; 
        }
    } else if (CheckCollisionPointRec(mousePosition, {game->window.x, game->window.y, game->window.width, 30}) &&
               CanBeDragged(game) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game->isDragable = true;
        SetWindowFirst(game);
        StartDragging(game);
    }
}

// okno nie musi być pierwsze, ale myszka nie może być w konflikcie z pierszym oknem
// (!CheckCollisionPointRec(mousePosition, games.back()->window))


bool MiniGameManager::CanBeDragged(std::shared_ptr<MiniGame>& game) {
    if (!currentlyDragged)
        return true;
    return false;
}

void MiniGameManager::StartDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged = game;
}

void MiniGameManager::StopDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged.reset();
}

void MiniGameManager::Close(std::shared_ptr<MiniGame>& game) {
    game->isOpen = false;
    auto it = std::find(games.begin(), games.end(), game);
    games.erase(it);
    currentlyDragged.reset();
    activeGame.reset();
}