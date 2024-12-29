#ifndef MINI_GAME_H
#define MINI_GAME_H

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "raylib.h"

// Unified MiniGame class
class MiniGame {
public:
    MiniGame(float x, float y, float width, float height, const std::string& title);
    virtual ~MiniGame(); // Add this line

    Rectangle window;      // Game window dimensions
    std::string title;     // Title of the window
    bool isDragable;       // Is the window being dragged?
    bool isOpen;           // Is the game window open?
    // bool isFirst;         // Is Game Window Active?
    bool gameComplete;     // Is Game Complete?
    float dotTimer;        // Timer flag for flashing dot (better not use)

    // Virtual methods for game-specific behavior
    virtual void Update(); // To be overridden for specific logic
    virtual void Draw();   // To be overridden for specific logic

    // Window management
    void Close();
};

#endif // MINI_GAME_H