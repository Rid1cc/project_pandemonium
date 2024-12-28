#ifndef BALL_GAME_H
#define BALL_GAME_H

#include "../headers/MiniGameManager.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
using namespace std;

class Ball {
public:
    float x, y;
    int radius;
    int speed;
    void draw();
};

class Rec1 {
public:
    float x, y;
    int speed_y;
    float window_width;
    float window_height;

    Rec1(float win_width, float win_height) : window_width(win_width), window_height(win_height) {}
    void draw();
    void update();
};

class Rec2 {
public:
    float x, y;
    int speed_y;
    float window_width;
    float window_height;

    Rec2(float win_width, float win_height) : window_width(win_width), window_height(win_height) {}
    void draw();
    void update();
};

class Rec3 {
public:
    float x, y;
    int speed_y;
    float window_width;
    float window_height;

    Rec3(float win_width, float win_height) : window_width(win_width), window_height(win_height) {}
    void draw();
    void update();
};

class BallGame : public MiniGame {
private:
    Color kolor;
    Ball ball;
    Rec1 rec1;
    Rec2 rec2;
    Rec3 rec3;
    void BallReset();
    void GameOver();

public:
    BallGame(float x, float y, float width, float height, const std::string& title);
    ~BallGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // BALL_GAME_H
