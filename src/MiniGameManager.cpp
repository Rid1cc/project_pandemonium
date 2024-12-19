#include "./headers/MiniGameManager.h"

// Constructor
MiniGameManager::MiniGameManager()
    : totalTime(60.0f),      // Default total time (e.g., 60 seconds)
      elapsedTime(0.0f),
      timerActive(false),
      showEndMessage(false),
      messageTimer(0.0f),
      endMessage(""),
      win(false) {}

// Optional: Method to set the total time
void MiniGameManager::SetTotalTime(float duration) {
    totalTime = duration;
}

// Add a game to the manager
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game) {
    games.push_back(game);
    if (!timerActive) {
        StartTimer(totalTime); // Start the timer when the first game is added
    }
}

// Start the timer with a specified duration
void MiniGameManager::StartTimer(float duration) {
    totalTime = duration;
    elapsedTime = 0.0f;
    timerActive = true;
}

// Reset the timer
void MiniGameManager::ResetTimer() {
    elapsedTime = 0.0f;
    timerActive = false;
}

// Check if the timer has expired
bool MiniGameManager::IsTimeUp() const {
    return elapsedTime >= totalTime;
}

// Set the end message based on win/loss
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

// Update the timer
void MiniGameManager::UpdateTimer() {
    if (timerActive) {
        elapsedTime += GetFrameTime();
        if (IsTimeUp()) {
            timerActive = false;
            SetEndMessage(false); // Player failed to complete in time
            // Handle timer expiry by closing all remaining games
            while (!games.empty()) {
                Close(games.back());
            }
            // Optionally, trigger additional loss logic here
        }
    }
}

// Close a game and check for win condition
void MiniGameManager::Close(std::shared_ptr<MiniGame>& game) {
    game->isOpen = false;
    auto it = std::find(games.begin(), games.end(), game);
    games.erase(it);
    currentlyDragged.reset();
    activeGame.reset();

    if (games.empty() && timerActive) {
        SetEndMessage(true); // Player successfully completed all games
        timerActive = false; // Stop the timer as all games are done
    }
}

// Update all active games and handle end-of-level conditions
void MiniGameManager::Update() {
    // Update the timer first
    UpdateTimer();

    // Update all active games
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DragWindow(game, GetMousePosition());
            if (IsWindowFirst(game)) {
                game->Update();
            }
        }
        // Close game if conditions are met
        if ((CheckCollisionPointRec(GetMousePosition(), {game->window.x + game->window.width - 20, game->window.y, 20, 20}) &&
             IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBeInteracted(game, GetMousePosition())) || game->gameComplete) {
            Close(game);
        }
    }

    // Update message timer if an end message is being shown
    if (showEndMessage) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 1.0f) { // 1 second has passed
            showEndMessage = false;
            // Optionally, trigger level transition or other actions here
        }
    }
}

// Draw all games, the timer, and the end message
void MiniGameManager::Draw() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DrawRectangleRec(game->window, BLACK);
            if (!IsWindowFirst(game)) DrawRectangleLinesEx(game->window, 2, ORANGE);
            else DrawRectangleLinesEx(game->window, 2, Color{0, 94, 255, 255});
            //DrawRectangleLinesEx(window, 2, ORANGE);
            DrawText(game->title.c_str(), game->window.x + 10, game->window.y + 10, 20, WHITE);
            DrawText("x", game->window.x + game->window.width - 15, game->window.y + 5, 20, RED);
            game->Draw();
        }
    }

    // Draw the timer
    if (timerActive) {
        float remainingTime = totalTime - elapsedTime;
        if (remainingTime < 0.0f) remainingTime = 0.0f;
        std::string timerText = "Time Left: " + std::to_string(static_cast<int>(remainingTime)) + "s";
        // Position the timer text at the top-center of the screen
        int screenWidth = GetScreenWidth();
        DrawText(timerText.c_str(), screenWidth / 2 - MeasureText(timerText.c_str(), 20) / 2, 10, 20, YELLOW);
    }

    // Draw the end message if applicable
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
}

// Set window to the front
void MiniGameManager::SetWindowFirst(std::shared_ptr<MiniGame>& game) {
    auto it = std::find(games.begin(), games.end(), game);
    if (it != games.end() && !CheckCollisionPointRec(GetMousePosition(), games.back()->window)) {
        std::iter_swap(it, games.end() - 1);
    }
}

// Check if a game can be interacted with
bool MiniGameManager::CanBeInteracted(std::shared_ptr<MiniGame>& game, Vector2 mousePosition) {
    if (game == games.back() && CheckCollisionPointRec(mousePosition, game->window))
        return true;
    return false;
}

// Check if a window is the first (topmost)
bool MiniGameManager::IsWindowFirst(std::shared_ptr<MiniGame>& game) {
    if (game == games.back())
        return true;
    return false;
}

// Drag the window if applicable
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

// Check if a game can be dragged
bool MiniGameManager::CanBeDragged(std::shared_ptr<MiniGame>& game) {
    if (!currentlyDragged)
        return true;
    return false;
}

// Start dragging a game
void MiniGameManager::StartDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged = game;
}

// Stop dragging a game
void MiniGameManager::StopDragging(std::shared_ptr<MiniGame>& game) {
    currentlyDragged.reset();
}
