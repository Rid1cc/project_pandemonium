#include "GameplayManager.h"

// int randomW;
//         int randomH;
//         if(framesCounter%3==0){
//         for(int i =0; i<=20; i++){
//             std::uniform_int_distribution<int> rW(50, screenWidth-100);
//             std::uniform_int_distribution<int> rH(25, screenHeight-50);
//             randomW = rW(rng);
//             randomH = rH(rng);
//             DrawText("-", randomW, randomH, 10, primaryColor);
//             }
//         }

GameplayManager::GameplayManager() : 
    difficulty(1)
    { 
}

GameplayManager::~GameplayManager() {
    // Destructor implementation
}

void GameplayManager::gameplayInit() {
    gameplayEvent.subscribe("startGame", [this]() { this->onStartCommand(); });
    gameplayEvent.subscribe("stopGame", [this]() { this->onStopCommand(); });
}

void GameplayManager::gameplayEnd() {
    // Cleanup code

    // Unsubscribe from events if necessary
    gameplayEvent.unsubscribe("startGame", [this]() { this->onStartCommand(); });
    gameplayEvent.unsubscribe("stopGame", [this]() { this->onStopCommand(); });
}

// Event handler for "startGame" command
void GameplayManager::onStartCommand() {
    // Handle start game event
    std::cout << "Game Started with difficulty level: " << difficulty << std::endl;
    // Additional start game logic
}

// Event handler for "stopGame" command
void GameplayManager::onStopCommand() {
    // Handle stop game event
    std::cout << "Game Stopped." << std::endl;
    // Additional stop game logic
}

