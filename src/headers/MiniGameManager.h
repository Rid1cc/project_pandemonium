#ifndef MINI_GAME_MANAGER_H
#define MINI_GAME_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "raylib.h"

// Unified MiniGame class
class MiniGame {
protected:
    Rectangle window;        // Game window dimensions
    std::string title;     // Title of the window
    bool isDragging;       // Is the window being dragged?
    Vector2 dragOffset;    // Drag offset
    bool isOpen;           // Is the game window open?

public:
    MiniGame(float x, float y, float width, float height, const std::string& title);

    // Virtual methods for game-specific behavior
    virtual void Update(); // To be overridden for specific logic
    virtual void Draw();   // To be overridden for specific logic

    // Window management
    void HandleDrag();
    void DrawWindow();
    void Close();

    // Is the window open?
    bool IsOpen() const;
};

// MiniGameManager handles multiple MiniGames
class MiniGameManager {
private:
    std::vector<std::shared_ptr<MiniGame>> games; // List of mini-games

public:
    void AddGame(const std::shared_ptr<MiniGame>& game);
    void Update();
    void Draw();
};

#endif // MINI_GAME_MANAGER_H
