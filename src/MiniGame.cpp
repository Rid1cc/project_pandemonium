#include "./headers/MiniGame.h"
#include "./headers/player.h"

// MiniGame Constructor
MiniGame::MiniGame(float x, float y, float width, float height, const std::string& title)
    : window({x, y, width, height}), 
    title(title), 
    gameComplete(false), 
    isOpen(true), 
    dotTimer(0.0f),
    totalTimer(15.0f),
    elapsedTime(0.0f),
    isTimerActive(false) {
        //SetMiniGameTimer(duration);
        StartTimer();
    }

// MiniGame Destructor
MiniGame::~MiniGame() {
    // ...existing cleanup code if any...
}

// Base Update method (can be overridden)
void MiniGame::Update() {

}

// Base Draw method (can be overridden)
void MiniGame::Draw() {
}

void MiniGame::Close() {
    isOpen = false;
}

void MiniGame::UpdateMiniGameTimer() {
    if (IsTimeUp()) {OnTimerEnd();}
    else if (isTimerActive) {
        elapsedTime += GetFrameTime();
        if (elapsedTime > totalTimer) elapsedTime = totalTimer;
    }
}

void MiniGame::StartTimer() {
    if (!isTimerActive) isTimerActive = true;
}

void MiniGame::StopTimer() {
    if (isTimerActive) isTimerActive = false;
}

void MiniGame::ResetTimer() {
    elapsedTime = 0.0f;
    isTimerActive = false;
}

void MiniGame::SetMiniGameTimer(float newDuration) {
    totalTimer = newDuration;
}

bool MiniGame::IsTimeUp() const {
    return (elapsedTime >= totalTimer);
}

void MiniGame::OnTimerEnd() {
    StopTimer();
    isOpen = false;
}

float MiniGame::RemainingTime() const{
    return (totalTimer - elapsedTime);
}