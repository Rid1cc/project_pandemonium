#include "../headers/MiniGameManager.h"
#include "../headers/globals.h"
#include "../minigames/TypeGame.h" // Ensure this include is present
#include "../minigames/ConnectWiresGame.h"
#include "../minigames/BallGame.h"
#include "../minigames/FinderGame.h"
#include "../gameplay/gameplay_vars.h"
#include "GameplayManager.h"
#include "EventManager.h"
#include <random>

// Constructor initializes timer and state variables
MiniGameManager::MiniGameManager()
    : startGameSequences(false),
      gameDurationScale(1),
      arePlayersAlive(true),
      //miniGamesDurationTime(15.0f),
      showEndMessage(false),
      messageTimer(0.0f),
      endMessage(""),
      win(false),
      gameType(0),
      //isSafeMarginTimerOn(false),
      isConnectingGameOn(false),
      isTypeGameOn(false),
      isBallGameOn(false),
      isFinderGameOn(false) {}

void MiniGameManager::gameplayEnd() {
    for ( auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
        Close(game);
    }
    // for (auto& game : games) {
    //     Close(game);
    // }
}

// Update method called every frame to manage games and timer
void MiniGameManager::Update() {
    //UpdateTimer(); // Update the global timer
    IsLevelCompleted();
    if (startGameSequences) RunGameSequence();    

    // Iterate through games in reverse order for proper layering
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            game->UpdateMiniGameTimer();
            UpdateDotTimer(game); // Update visual dot timer
            DragWindow(game, mousePos); // Handle window dragging
            SetMouseState(mousePos, game);

            if (IsWindowFirst(game)) {
                game->Update(); // Update the topmost game
            }
        } else {Close(game);}

        // Check if the close button is clicked or the game is complete
        if ((CheckCollisionPointRec(mousePos, {game->window.x + game->window.width - 20, game->window.y, 20, 20}) &&
             IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBeInteracted(game, mousePos)) || game->gameComplete || game->gameLost) {
            Close(game); // Close the game window
        }
    }

    // // Handle end message display timing
    // if (showEndMessage) {
    //     messageTimer += GetFrameTime();
    //     if (messageTimer >= 1.0f) { 
    //         showEndMessage = false; // Hide the message after 1 second
    //     }
    // }

    // if(!gameplayManager.isSafeMarginTimerOn && !isMiniGameSequenceStarted) {
    //     isMiniGameSequenceStarted = true;
    //     printf("test\n");
    //     gameplayManager.gameplayEvent.triggerEvent("startMiniGames");
    // }


}

void MiniGameManager::SetMouseState(Vector2 mousePosition, std::shared_ptr<MiniGame>& game) {
    if (CheckCollisionPointRec(mousePosition, game->window) && !isMouseOnMiniGameWindow)
        isMouseOnMiniGameWindow = true;
    else if (!CheckCollisionPointRec(mousePosition, game->window) && isMouseOnMiniGameWindow)
        isMouseOnMiniGameWindow = false;
}

bool MiniGameManager::CheckMouseState() const {
    return isMouseOnMiniGameWindow;
}

// Draw method called every frame to render games and UI elements
void MiniGameManager::Draw() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DrawRectangleRec(game->window, BLACK); // Draw game window background
            DrawRectangleLinesEx(game->window, 2, primaryColor); // Draw window border

            // Draw flashing dot indicator
            if (((int)game->dotTimer % 2) != 0)
                DrawCircle(game->window.x + 6, game-> window.y + 6, 2, primaryColor);
            
            // Draw remaining time
            float leftTime = game->totalTimer - game->elapsedTime;
            std::string timeLeftText = std::to_string(static_cast<int>(leftTime));
            DrawText(timeLeftText.c_str(), game->window.x + game->window.width - 50, game->window.y + 5, 20, primaryColor);

            DrawText(game->title.c_str(), game->window.x + 10, game->window.y + 10, 20, WHITE); // Draw window title
            DrawText("x", game->window.x + game->window.width - 15, game->window.y + 5, 20, RED); // Draw close button
            game->Draw(); // Draw the mini-game content
        }
    }

    // Draw the global timer if active
    // if (timerActive) {
    //     float remainingTime = totalTime - elapsedTime;
    //     if (remainingTime < 0.0f) remainingTime = 0.0f;
    //     std::string dotTimerText = "Time Left: " + std::to_string(static_cast<int>(remainingTime)) + "s";
        
    //     // Position the timer text at the top-center of the screen
    //     int screenWidth = GetScreenWidth();
    //     DrawText(dotTimerText.c_str(), screenWidth / 2 - MeasureText(dotTimerText.c_str(), 20) / 2, 10, 20, primaryColor);
    // }

    // Draw the end message if applicable //DON'T DELETE THIS!!!
    /*
    if (showEndMessage) {
        // Calculate the position for the message (e.g., center of the screen)
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int fontSize = 40;
        int textWidth = MeasureText(endMessage.c_str(), fontSize);
        // Choose color based on win or loss
        Color textColor = win ? GREEN : RED;
        DrawText(endMessage.c_str(), (screenWidth - textWidth) / 2, screenHeight / 2 - fontSize, fontSize, textColor);
    }
    */
}

// Updates the dot timer for visual indicators in a specific game
void MiniGameManager::UpdateDotTimer(std::shared_ptr<MiniGame>& game) {
    if(IsWindowFirst(game)) 
        game->dotTimer += GetFrameTime();
    else if (game->dotTimer >= 0.0f)
        game->dotTimer = 0.0f;
}

// Sets the specified game window to be the topmost window
void MiniGameManager::SetWindowFirst(std::shared_ptr<MiniGame>& game) {
    auto it = std::find(games.begin(), games.end(), game);
    if (it != games.end() && !CheckCollisionPointRec(mousePos, games.back()->window)) {
        std::iter_swap(it, games.end() - 1); // Swap to make it the last element (topmost)
    }
}

// Determines if a game window can be interacted with based on its position
bool MiniGameManager::CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition) {
    if (game == games.back() && CheckCollisionPointRec(mousePosition, game->window))
        return true;
    return false;
}

// Checks if the game window is the topmost window
bool MiniGameManager::IsWindowFirst(std::shared_ptr<MiniGame>& game) {
    if (game == games.back())
        return true;
    return false;
}

// Handles dragging of game windows based on mouse input
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
        SetWindowFirst(game); // Bring window to front
        StartDragging(game); // Begin dragging
    }
}

// Determines if a game window can be dragged (no other window is being dragged)
bool MiniGameManager::CanBeDragged(std::shared_ptr<MiniGame>& game) {
    if (!currentlyDragged)
        return true;
    return false;
}

// Starts dragging the specified game window
void MiniGameManager::StartDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged = game;
}

// Stops dragging the specified game window
void MiniGameManager::StopDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged.reset();
}

// // Sets the total duration for the global timer
// void MiniGameManager::SetTotalTime(float duration) {
//     totalTime = duration;
// }

// Adds a new mini-game to the manager and starts the timer if not active
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game, float duration) {
    game->SetMiniGameTimer(duration);
    games.push_back(game);
    // if (!timerActive) {
    //     StartTimer(totalTime); 
    // }
}

// Initializes and starts the global timer with a specified duration
// void MiniGameManager::StartTimer(float duration) {
//     totalTime = duration;
//     elapsedTime = 0.0f;
//     timerActive = true;
// }

// // Resets the global timer and deactivates it
// void MiniGameManager::ResetTimer() {
//     elapsedTime = 0.0f;
//     timerActive = false;
// }

// // Checks if the global timer has reached or exceeded the total time
// bool MiniGameManager::IsTimeUp() const {
//     return elapsedTime >= totalTime;
// }

// Sets and displays the end message based on whether the player won or lost
void MiniGameManager::SetEndMessage(bool isWin) {
    if (isWin) {
        endMessage = "Level Completed!";
    } else {
        endMessage = "Time's up! Level Failed!";
    }
    showEndMessage = true;
    messageTimer = 0.0f;
    win = isWin;
}

// // Updates the global timer and handles the scenario when time is up
// void MiniGameManager::UpdateTimer() {
//     if (timerActive) {
//         elapsedTime += GetFrameTime();
//         if (IsTimeUp()) {
//             timerActive = false;
//             SetEndMessage(false); // Set loss message
//             while (!games.empty()) {
//                 Close(games.back()); // Close all open games
//             }
//         }
//     }
// }

// void MiniGameManager::AddTime(float timeAmount) {
//     elapsedTime -= timeAmount;
// }

// Closes and removes a mini-game from the manager
void MiniGameManager::Close(std::shared_ptr<MiniGame>& game) {
    if (game->isOpen == true) game->isOpen = false;
    auto it = std::find(games.begin(), games.end(), game);
    switch (SelectedDifficulty)
        {
        case 1:
            if (game->gameComplete) {
            gameplayManager.enemy.takeDamage(10);
            printf("enemy hp -17\n");
            gameplayManager.player.heal(5);
            printf("player hp +5\n");
            } else { gameplayManager.player.takeDamage(5); 
                     printf("player hp -10\n"); }
            break;
        case 2:
            if (game->gameComplete) {
            gameplayManager.enemy.takeDamage(5);
            } else { gameplayManager.player.takeDamage(5); }
            break;
        case 3:
            if (game->gameComplete) {
            gameplayManager.enemy.takeDamage(5);
            } else { gameplayManager.player.takeDamage(10); }
            break;
        default:
            break;
        }

    if (dynamic_cast<ConnectWiresGame*>(game.get())) {
        isConnectingGameOn = false;
        std::cout << "connecting game off\n";
        }
    else if (dynamic_cast<FinderGame*>(game.get())) {
        isFinderGameOn = false;
        std::cout << "finder game off\n";}
    else if (dynamic_cast<TypeGame*>(game.get())) {
        isTypeGameOn = false;
        std::cout << "Type game off\n";
        }
    else if (dynamic_cast<BallGame*>(game.get())) {
        isBallGameOn = false;
        std::cout << "Ball game off\n";
        }

    games.erase(it); // Remove the game from the list
    currentlyDragged.reset();
    activeGame.reset();
    isMouseOnMiniGameWindow = false;

    // If all games are closed and timer is active, show win message
    // if (games.empty()) {
    //     SetEndMessage(true); // Set win message
    //     printf("none minigame exists\n");
    //     //timerActive = false;
    // }
}

bool MiniGameManager::allGamesClosed() const {
    for (const auto& game : games) {
        if (game->isOpen) {
            return false;
        }
    }
    return true;
}

bool MiniGameManager::hasActiveTypeGame() const {
    for (const auto& game : games) {
        if (dynamic_cast<TypeGame*>(game.get()) && game->isOpen) {
            return true;
        }
    }
    return false;
}


void MiniGameManager::RunGameSequence() {
    // zaktualizuj timer jeśli jest aktywny
    if (isIntervalTimerOn && IntervalTimer > 0.0f) {
        IntervalTimer -= GetFrameTime();
    }
    // sprawdź czy wektor gier jest pusty
    if (allGamesClosed()) {
        if (isIntervalTimerOn == false) {
            IntervalTimer = IntervalTimerSetTime;
            isIntervalTimerOn = true;
            }
        if (IntervalTimer <= 0.0f) {
            int dif = SelectedDifficulty;
            for (int i = 0; i < dif; i++){
                auto randomGame = GetRandomGame();
                randomGame();
            }
            isIntervalTimerOn = false;
        }
    }
}

int MiniGameManager::GetRandomIntInRange(int begin, int end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(begin, end);

    return dis(gen);
}


std::function<void()> MiniGameManager::GetRandomGame() {
    int gameType = GetRandomIntInRange(1, 4);

    switch (gameType)
    {
    case 1:
        return [this]() { this->StartBallGame(gameDurationScale); };
    case 2:
        return [this]() { this->StartConnectingGame(gameDurationScale); };
    case 3:
        return [this]() { this->StartFinderGame(gameDurationScale); };
    case 4:
        return [this]() { this->StartTypingGame(gameDurationScale); };
    default:
        return []() { /* pusta funkcja */ };
    }
}

void MiniGameManager::ManageGameSequences(const int& difficulty) {
    auto randomGame = GetRandomGame();

    switch (difficulty)
    {
    case 1:
        IntervalTimerSetTime = (float)GetRandomIntInRange(30, 60);
        IntervalTimer = IntervalTimerSetTime;
        gameDurationScale = 1.0f;
        randomGame();
        break;
    case 2:
        IntervalTimerSetTime = (float)GetRandomIntInRange(30, 60);
        IntervalTimer = IntervalTimerSetTime;
        gameDurationScale = 1.8f;
        randomGame();
        randomGame = GetRandomGame();
        randomGame();
        break;
    case 3:
        IntervalTimerSetTime = (float)GetRandomIntInRange(30, 60);
        IntervalTimer = IntervalTimerSetTime;
        gameDurationScale = 2.4f;
        randomGame();
        randomGame = GetRandomGame();
        randomGame();
        randomGame = GetRandomGame();
        randomGame();
        break;
    default:
        break;
    }
    startGameSequences = true;
}

void MiniGameManager::StartConnectingGame(float& durationScale) {
    auto connectWires = std::make_shared<ConnectWiresGame>(GetRandomIntInRange(screen.x, screen.width - 400), 
                                                           GetRandomIntInRange(screen.y, screen.height -  300), 
                                                           GetRandomIntInRange(300, 400), 
                                                           GetRandomIntInRange(200, 300), "SPLINTER-45");
    miniGamesManager.AddGame(connectWires, durationScale * 40.0f);
    isConnectingGameOn = true;
}

void MiniGameManager::StartTypingGame(float& durationScale) {
    auto type = std::make_shared<TypeGame>(GetRandomIntInRange(screen.x, screen.width - 1000), 
                                           GetRandomIntInRange(screen.y, screen.height - 400), 
                                           1000, 400, "REG.HACK");
    miniGamesManager.AddGame(type, durationScale * 60.0f);
    isTypeGameOn = true;
}

void MiniGameManager::StartFinderGame(float& durationScale) {
    auto finder = std::make_shared<FinderGame>(GetRandomIntInRange(screen.x, screen.width - 400), 
                                               GetRandomIntInRange(screen.y, screen.height -  300),
                                               400, 300, "BACKDOOR");
    miniGamesManager.AddGame(finder, durationScale * 40.0f);
    isFinderGameOn = true;
}

void MiniGameManager::StartBallGame(float& durationScale) {
    auto ballGame = std::make_shared<BallGame>(GetRandomIntInRange(screen.x, screen.width - 650),
                                                       GetRandomIntInRange(screen.y, screen.height - 550),
                                                       GetRandomIntInRange(300, 500), 
                                                       GetRandomIntInRange(250, 400), "PKG SPOOF");
    miniGamesManager.AddGame(ballGame, durationScale * 70.0f);    
    isBallGameOn = true;
}

bool MiniGameManager::IsLevelCompleted() {
    if (gameplayManager.player.getHealth() > 0 && gameplayManager.enemy.getHealth() > 0) {
        return false;
    } else {
        gameplayManager.gameplayEvent.triggerEvent("stopGame");
        gameplayManager.gameplayEnd();
        if (gameplayManager.enemy.getHealth() == 0){
            DifficultyCompleted(SelectedDifficulty);
            currentScreen = TITLE;
            return true;
        }
    }
    return false; // Ensure the function returns a boolean value
}
