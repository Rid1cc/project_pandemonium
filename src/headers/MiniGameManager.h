#ifndef MINI_GAME_MANAGER_H
#define MINI_GAME_MANAGER_H

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "raylib.h"

class MiniGameManager;

// Unified MiniGame class
class MiniGame : public std::enable_shared_from_this<MiniGame> {
protected:
    bool isDragable;       // Is the window being dragged?
    bool isOpen;           // Is the game window open?
    std::string title;     // Title of the window
    Rectangle window;        // Game window dimensions
    Vector2 dragOffset;    // Drag offset
    MiniGameManager* manager;
    bool gameComplete = {false};
    bool isOnTop;

public:
    MiniGame(float x, float y, float width, float height, const std::string& title);
    ~MiniGame() = default;

    // Virtual methods for game-specific behavior
    virtual void Update(); // To be overridden for specific logic
    virtual void Draw();   // To be overridden for specific logic

    // Window management
    void HandleDrag(Vector2 mousePosition);
    void DrawWindow();
    void Close();
    std::shared_ptr<MiniGame> GetThis()  {
        return shared_from_this(); // Zwraca std::shared_ptr do bieżącego obiektu
    };
    void SetManager(MiniGameManager* mgr) {manager = mgr; }
    bool CanBeDragged(Vector2 mousePosition);



    // Is the window open?
    bool IsOpen() const;
    void StopDragging();
};



// MiniGameManager handles multiple MiniGames
class MiniGameManager {
private:
    std::vector<std::shared_ptr<MiniGame>> games; // List of mini-games

public:

    void AddGame(const std::shared_ptr<MiniGame>& game);
    void Update();
    void Draw();
    void BringToFront(std::shared_ptr<MiniGame> game);
    std::shared_ptr<MiniGame> currentlyDragged;
    std::shared_ptr<MiniGame> onTop;
};

#endif // MINI_GAME_MANAGER_H
