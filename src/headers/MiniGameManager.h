#ifndef MINI_GAME_MANAGER_H
#define MINI_GAME_MANAGER_H

#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include "raylib.h"
#include "MiniGame.h"
#include "../gameplay/gameplay_vars.h"

// MiniGameManager handles multiple MiniGames
enum class GameType {
    None,
    BALLGAME,
    WIREGAME,
    TYPINGGAME,
    FINDERGAME
};

class MiniGameManager {
private:
    std::vector<std::shared_ptr<MiniGame>> games; // List of mini-games
    std::shared_ptr<MiniGame> currentlyDragged;   // Currently dragged game window
    std::shared_ptr<MiniGame> activeGame;         // Currently active game
    bool isMouseOnMiniGameWindow;

    // Timer variables
    //float totalTime;       // Total time allotted in seconds
    //float elapsedTime;     // Time elapsed since the timer started
    //bool timerActive;      // Flag to indicate if the timer is running

    // End message variables
    bool showEndMessage;          // Flag to indicate if the end message should be shown
    float messageTimer;           // Timer to track how long the message has been displayed
    std::string endMessage;       // The message to display ("Level Completed!" or "Time's up! Level Failed!")
    bool win;                      // Flag to indicate if the level was completed successfully

    // Timer methods
    //void StartTimer(float duration); // Initializes and starts the global timer
    //void ResetTimer();               // Resets the global timer
    //void UpdateTimer();              // Updates the timer each frame
    // bool IsTimeUp() const;           // Checks if the timer has expired
    //void AddTime(float timeAmount);

    int gameType;
    

    // Message display methods
    void SetEndMessage(bool isWin);  // Sets the end message based on win/loss

    // Dragging and window management methods
    bool CanBeDragged(std::shared_ptr<MiniGame>& game); // Checks if a game can be dragged
    void StartDragging(std::shared_ptr<MiniGame>& game); // Begins dragging a game window
    void StopDragging(std::shared_ptr<MiniGame>& game);  // Stops dragging a game window
    void DragWindow(std::shared_ptr<MiniGame>& game, Vector2 mousePosition); // Handles window dragging logic

    void SetMouseState(Vector2 mousePosition, std::shared_ptr<MiniGame>& game);
    void SetWindowFirst(std::shared_ptr<MiniGame>& game); // Brings a window to the front
    bool CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition); // Checks if a window can be interacted with
    bool IsWindowFirst(std::shared_ptr<MiniGame>& game); // Determines if a window is the topmost
    void UpdateDotTimer(std::shared_ptr<MiniGame>& game); // Updates the dot timer for visual indicators

    void Close(std::shared_ptr<MiniGame>& game); // Closes and removes a game from the manager

public:
    MiniGameManager(); // Constructor
    ~MiniGameManager() = default;

    // Game management methods
    void AddGame(const std::shared_ptr<MiniGame>& game); // Adds a new mini-game to the manager

    // Core loop methods
    void Update(); // Updates all managed games and timers
    void Draw();   // Draws all managed games and UI elements

    // Timer configuration
    //void SetTotalTime(float duration); // Sets the total duration for the timer

    bool allGamesClosed() const; // Add this line
    bool CheckMouseState() const;
    bool hasActiveTypeGame() const; // Ensure this line exists

    void StartGameSequences(int difficulty);
    void StartConnectingGame();
    void StartTypingGame();
    void StartFinderGame();
    void StartBallGame();

    bool isSafeMarginTimerOn;

};

#endif // MINI_GAME_MANAGER_H
