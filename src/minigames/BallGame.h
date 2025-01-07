// BallGame.h
#ifndef BALL_GAME_H
#define BALL_GAME_H

#include "../headers/MiniGameManager.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <vector>
using namespace std;

class BallGame : public MiniGame {
private:
    // Punktacja
    int score;
    int maxScore;
    
    // Liczba prób
    int attempts;
    int maxAttempts;
    
    bool gameOver;

    // Integrated Ball properties
    float ball_x, ball_y;
    int ball_radius;
    int ball_speed;

    // Integrated Rectangle properties
    struct RectangleEntity {
        float x, y;
        float speed_y;
    };
    std::vector<RectangleEntity> rectangles;

    // Window dimensions
    float window_width;
    float window_height;

    // Private methods
    void BallReset();
    void GameOver();
    void DrawBall();
    void DrawRectangles();
    void UpdateRectangles();
    void HandleCollision();
    void CheckScore();
    void IncreaseDifficulty();
    void ResetGame();

public:
    BallGame(float x, float y, float width, float height, const std::string& title);
    ~BallGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // BALL_GAME_H
