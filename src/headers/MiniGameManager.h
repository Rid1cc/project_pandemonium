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

public:

    void AddGame(const std::shared_ptr<MiniGame>& game);
    void Update();
    void Draw();
    void DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition);
    // bool IsBeingUsed(std::shared_ptr<MiniGame>& game);
    void SetWindowFirst(std::shared_ptr<MiniGame> game);
    //bool IsFirst(std::vector<std::shared_ptr<MiniGame>>::iterator& game);

    bool CanBeActive(std::shared_ptr<MiniGame>& game);
    void SetActivate(std::shared_ptr<MiniGame>& game);
    void SetNeutral(std::shared_ptr<MiniGame>& game);
    
    bool CanBeDragged(std::shared_ptr<MiniGame>& game);
    void StartDragging(std::shared_ptr<MiniGame>& game);
    void StopDragging(std::shared_ptr<MiniGame>& game);
    std::shared_ptr<MiniGame> currentlyDragged;
    std::shared_ptr<MiniGame> activeGame;


    void Close(std::shared_ptr<MiniGame>& game);            //Close game
};

#endif // MINI_GAME_MANAGER_H
