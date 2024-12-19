#ifndef MINI_GAME_MANAGER_H
#define MINI_GAME_MANAGER_H

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "raylib.h"
#include "MiniGame.h"


// MiniGameManager handles multiple MiniGames
class MiniGameManager {
private:
    std::vector<std::shared_ptr<MiniGame>> games; // List of mini-games
    std::shared_ptr<MiniGame> currentlyDragged;
    std::shared_ptr<MiniGame> activeGame;
    
    bool CanBeDragged(std::shared_ptr<MiniGame>& game);
    void StartDragging(std::shared_ptr<MiniGame>& game);
    void StopDragging(std::shared_ptr<MiniGame>& game);
    void DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition);

    void SetWindowFirst(std::shared_ptr<MiniGame>& game);
    bool CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition);
    bool IsWindowFirst(std::shared_ptr<MiniGame>& game);

    void Close(std::shared_ptr<MiniGame>& game);

public:
    void AddGame(const std::shared_ptr<MiniGame>& game);
    void Update();
    void Draw();
};

#endif // MINI_GAME_MANAGER_H
