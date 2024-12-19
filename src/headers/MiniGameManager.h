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

    // Timer variables
    float totalTime;       // Total time allotted in seconds
    float elapsedTime;     // Time elapsed since the timer started
    bool timerActive;      // Flag to indicate if the timer is running

    // End message variables
    bool showEndMessage;          // Flag to indicate if the end message should be shown
    float messageTimer;           // Timer to track how long the message has been displayed
    std::string endMessage;       // The message to display ("Level Completed!" or "Time's up! Level Failed!")
    bool win;                      // Flag to indicate if the level was completed successfully

    // Timer methods
    void StartTimer(float duration);
    void ResetTimer();
    void UpdateTimer();
    bool IsTimeUp() const;

    // Message display methods
    void SetEndMessage(bool isWin);

    // Existing methods
    bool CanBeDragged(std::shared_ptr<MiniGame>& game);
    void StartDragging(std::shared_ptr<MiniGame>& game);
    void StopDragging(std::shared_ptr<MiniGame>& game);
    void DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition);

    void SetWindowFirst(std::shared_ptr<MiniGame>& game);
    bool CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition);
    bool IsWindowFirst(std::shared_ptr<MiniGame>& game);

    void Close(std::shared_ptr<MiniGame>& game);

public:
    MiniGameManager();

    void AddGame(const std::shared_ptr<MiniGame>& game);
    void Update();
    void Draw();

    // Optional: Method to set the timer duration
    void SetTotalTime(float duration);
};

#endif // MINI_GAME_MANAGER_H
