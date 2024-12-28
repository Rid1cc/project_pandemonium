// BallGame.cpp
#include "BallGame.h"

using namespace std;

BallGame::BallGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title),
        rec1(width, height),
        rec2(width, height),
        rec3(width, height)
        {
        ball.radius = 20;
        ball.x = 20;
        ball.y = window.height / 2;
        rec1.x = window.width / 2;
        rec1.y = window.height / 2 - 50;
        rec2.x = window.width / 2 - 100;
        rec2.y = window.height / 2 - 75;
        rec3.x = window.width / 2 + 100;
        rec3.y = window.height / 2 + 75;
        rec1.speed_y = 10;
        rec2.speed_y = -12;
        rec3.speed_y = 9;
}

void BallGame::BallReset(){
    ball.x = 20;
    ball.y = 400;
}

void BallGame::GameOver(){
    DrawText("GameOver", window.width - 100, (window.height / 4)- 100, 80, WHITE);
}

void BallGame::Update(){
    if(IsKeyDown(KEY_RIGHT)){
        ball.x += 6;
    }
    else if(IsKeyDown(KEY_LEFT)){
        ball.x -= 6;
    }
    else if(IsKeyDown(KEY_DOWN)){
        ball.y += 6;
    }
    else if(IsKeyDown(KEY_UP)){
        ball.y -= 6;
    }
    rec1.update();
    rec2.update();
    rec3.update();
}

void BallGame::Draw(){
    if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{rec1.x, rec1.y, 50, 200})){
        GameOver();
        BallReset();
    }
    if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{rec2.x, rec2.y, 50, 200})){
        GameOver();
        BallReset();
    }
    if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{rec3.x, rec3.y, 50, 200})){
        GameOver();
        BallReset();
    }
    ball.draw();
    rec1.draw();
    rec2.draw();
    rec3.draw();
}

void Rec1::draw(){
    DrawRectangle(x, y, 50, 200, BLUE);
}

void Rec1::update(){
    y += speed_y;
    if(y + 200 >= window_height || y <= 0){
        speed_y *= -1;
    }
}

void Rec2::draw(){
    DrawRectangle(x, y, 50, 200, BLUE);
}

void Rec2::update(){
    y += speed_y;
    if(y + 200 >= window_height || y <= 0){
        speed_y *= -1;
    }
}

void Rec3::draw(){
    DrawRectangle(x, y, 50, 200, BLUE);
}

void Rec3::update(){
    y += speed_y;
    if(y + 200 >= window_height || y <= 0){
        speed_y *= -1;
    }
}

void Ball::draw(){
    DrawCircle(x, y, radius, PINK);
}