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
    Color kolor;
    
    // Integrated Ball properties
    float ball_x, ball_y;
    int ball_radius;
    int ball_speed;
    
    // Integrated Rectangle properties
    struct RectangleEntity {
        float x, y;
        int speed_y;
    };
    std::vector<RectangleEntity> rectangles;
    
    float window_width;
    float window_height;

    void BallReset();
    void GameOver();
    void DrawBall();
    void DrawRectangles();
    void UpdateRectangles();
    void HandleCollision();

public:
    BallGame(float x, float y, float width, float height, const std::string& title);
    ~BallGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // BALL_GAME_H
