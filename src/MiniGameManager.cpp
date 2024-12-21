#include "./headers/MiniGameManager.h"
#include "./headers/globals.h"

// Constructor initializes timer and state variables
MiniGameManager::MiniGameManager()
    : totalTime(60.0f),      
      elapsedTime(0.0f),
      timerActive(false),
      showEndMessage(false),
      messageTimer(0.0f),
      endMessage(""),
      win(false) {}

// Update method called every frame to manage games and timer
void MiniGameManager::Update() {
    UpdateTimer(); // Update the global timer

    // Iterate through games in reverse order for proper layering
    for (auto it = games.rbegin(); it != games.rend(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            UpdateDotTimer(game); // Update visual dot timer
            DragWindow(game, mousePos); // Handle window dragging

            if (IsWindowFirst(game)) {
                game->Update(); // Update the topmost game
            }
        }

        // Check if the close button is clicked or the game is complete
        if ((CheckCollisionPointRec(mousePos, {game->window.x + game->window.width - 20, game->window.y, 20, 20}) &&
             IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBeInteracted(game, mousePos)) || game->gameComplete) {
            Close(game); // Close the game window
        }
    }

    // Handle end message display timing
    if (showEndMessage) {
        messageTimer += GetFrameTime();
        if (messageTimer >= 1.0f) { 
            showEndMessage = false; // Hide the message after 1 second
        }
    }
}

// Draw method called every frame to render games and UI elements
void MiniGameManager::Draw() {
    for (auto it = games.begin(); it != games.end(); ++it) {
        auto& game = *it;
        if (game->isOpen) {
            DrawRectangleRec(game->window, BLACK); // Draw game window background
            DrawRectangleLinesEx(game->window, 2, ORANGE); // Draw window border

            // Draw flashing dot indicator
            if (((int)game->dotTimer % 2) != 0)
                DrawCircle(game->window.x + 6, game-> window.y + 6, 2, ORANGE);
            
            DrawText(game->title.c_str(), game->window.x + 10, game->window.y + 10, 20, WHITE); // Draw window title
            DrawText("x", game->window.x + game->window.width - 15, game->window.y + 5, 20, RED); // Draw close button
            game->Draw(); // Draw the mini-game content
        }
    }

    // Draw the global timer if active
    if (timerActive) {
        float remainingTime = totalTime - elapsedTime;
        if (remainingTime < 0.0f) remainingTime = 0.0f;
        std::string timerText = "Time Left: " + std::to_string(static_cast<int>(remainingTime)) + "s";
        
        // Position the timer text at the top-center of the screen
        int screenWidth = GetScreenWidth();
        DrawText(timerText.c_str(), screenWidth / 2 - MeasureText(timerText.c_str(), 20) / 2, 10, 20, ORANGE);
    }

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

// Sets the total duration for the global timer
void MiniGameManager::SetTotalTime(float duration) {
    totalTime = duration;
}

// Adds a new mini-game to the manager and starts the timer if not active
void MiniGameManager::AddGame(const std::shared_ptr<MiniGame>& game) {
    games.push_back(game);
    if (!timerActive) {
        StartTimer(totalTime); 
    }
}

// Initializes and starts the global timer with a specified duration
void MiniGameManager::StartTimer(float duration) {
    totalTime = duration;
    elapsedTime = 0.0f;
    timerActive = true;
}

// Resets the global timer and deactivates it
void MiniGameManager::ResetTimer() {
    elapsedTime = 0.0f;
    timerActive = false;
}

// Checks if the global timer has reached or exceeded the total time
bool MiniGameManager::IsTimeUp() const {
    return elapsedTime >= totalTime;
}

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

// Updates the global timer and handles the scenario when time is up
void MiniGameManager::UpdateTimer() {
    if (timerActive) {
        elapsedTime += GetFrameTime();
        if (IsTimeUp()) {
            timerActive = false;
            SetEndMessage(false); // Set loss message
            while (!games.empty()) {
                Close(games.back()); // Close all open games
            }
        }
    }
}

// Closes and removes a mini-game from the manager
void MiniGameManager::Close(std::shared_ptr<MiniGame>& game) {
    game->isOpen = false;
    auto it = std::find(games.begin(), games.end(), game);
    games.erase(it); // Remove the game from the list
    currentlyDragged.reset();
    activeGame.reset();

    // If all games are closed and timer is active, show win message
    if (games.empty() && timerActive) {
        SetEndMessage(true); // Set win message
        timerActive = false;
    }
}
