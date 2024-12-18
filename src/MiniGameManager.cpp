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
            if (game == currentlyDragged || !currentlyDragged) {
                game->Update();
            }
        }
        // Close game
        if ((CheckCollisionPointRec(GetMousePosition(), {game->window.x + game->window.width - 20, game->window.y, 20, 20}) &&
             IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || game->gameComplete) {
            Close(game);
        }
    }
}

//Draw All games
void MiniGameManager::Draw() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            //if(game->isActive) DrawRectangleLinesEx(game->window, 2, Color {0,94,255,255}); //inverted orange
            game->Draw();
        }
    }
}


void MiniGameManager::SetWindowFirst(std::shared_ptr<MiniGame> game) {
    auto it = std::find(games.begin(), games.end(), game);
    if (it != games.end()) {
        games.erase(it);
        games.push_back(game);
        TraceLog(LOG_INFO, "Game %p set first in queue", game.get());
    }
}

void MiniGameManager::DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition) {
    if (game->isDragable && game == activeGame) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouseDelta = GetMouseDelta();
            game->window.x += mouseDelta.x;
            game->window.y += mouseDelta.y;
        } else {
            StopDragging(game);
            game->isDragable = false;
            // game->isActive = false;
        }
    } else if (CheckCollisionPointRec(mousePosition, {game->window.x, game->window.y, game->window.width, 30}) &&
               CanBeDragged(game) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        game->isDragable = true;
        activeGame.reset();
        activeGame = game;
        if (!game->isActive) game->isActive = true;
        StartDragging(game);
    }
}

//bool MiniGameManager::IsFirst(std::vector<std::shared_ptr<MiniGame>>::iterator& game_iterator) {
//    return game_iterator == games.begin();
//}


bool MiniGameManager::CanBeDragged(std::shared_ptr<MiniGame>& game) {
    if (!currentlyDragged) {
        //TraceLog(LOG_INFO, "Window %p can be dragged", game.get());
        return true;
    } else {
        //TraceLog(LOG_INFO, "Window %p cannot be dragged", game.get());
        return false;
    }
}

void MiniGameManager::StartDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged = game;
}

void MiniGameManager::StopDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged.reset();
}

void MiniGameManager::Close(std::shared_ptr<MiniGame>& game) {
    game->isOpen = false;
    currentlyDragged.reset();
    activeGame.reset();
}