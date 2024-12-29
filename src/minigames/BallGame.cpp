// BallGame.cpp
#include "BallGame.h"

using namespace std;

BallGame::BallGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title),
      window_width(width),
      window_height(height)
{
    // Initialize ball properties based on window size
    ball_radius = window_width * 0.05f;
    ball_x = window_width * 0.05f;
    ball_y = window_height / 2;
    ball_speed = 6;

    // Initialize rectangles' positions and speeds relative to window size
    RectangleEntity rect1;
    rect1.x = window_width / 2;
    rect1.y = window_height / 2 - (window_height * 0.1f);
    rect1.speed_y = static_cast<int>(window_height * 0.025f);
    
    RectangleEntity rect2;
    rect2.x = window_width / 2 - (window_width * 0.2f);
    rect2.y = window_height / 2 - (window_height * 0.15f);
    rect2.speed_y = -static_cast<int>(window_height * 0.03f);
    
    RectangleEntity rect3;
    rect3.x = window_width / 2 + (window_width * 0.2f);
    rect3.y = window_height / 2 + (window_height * 0.15f);
    rect3.speed_y = static_cast<int>(window_height * 0.0225f);
    
    rectangles.push_back(rect1);
    rectangles.push_back(rect2);
    rectangles.push_back(rect3);
}

void BallGame::BallReset(){
    ball_x = window_width * 0.05f;
    ball_y = window_height / 2;
}

void BallGame::GameOver(){
    DrawText("GameOver", window.width - 100, (window.height / 4) - 100, 80, WHITE);
}

void BallGame::DrawBall(){
    DrawCircle(window.x + ball_x, window.y + ball_y, ball_radius, PINK);
}

void BallGame::DrawRectangles(){
    for(auto &rect : rectangles){
        DrawRectangle(window.x + rect.x, window.y + rect.y, window_width * 0.05f, window_height * 0.4f, BLUE);
    }
}

void BallGame::UpdateRectangles(){
    for(auto &rect : rectangles){
        rect.y += rect.speed_y;
        if(rect.y + (window_height * 0.4f) >= window_height || rect.y <= 0){
            rect.speed_y *= -1;
        }
    }
}

void BallGame::HandleCollision(){
    for(auto &rect : rectangles){
        if(CheckCollisionCircleRec(Vector2{ball_x + window.x, ball_y + window.y}, ball_radius, Rectangle{rect.x + window.x, rect.y + window.y, window_width * 0.05f, window_height * 0.4f})){
            BallReset();
            break;
        }
    }
}

void BallGame::Update(){
    if(IsKeyDown(KEY_RIGHT)){
        ball_x += ball_speed;
    }
    if(IsKeyDown(KEY_LEFT)){
        ball_x -= ball_speed;
    }
    if(IsKeyDown(KEY_DOWN)){
        ball_y += ball_speed;
    }
    if(IsKeyDown(KEY_UP)){
        ball_y -= ball_speed;
    }

    // Ensure the ball stays within window bounds
    if(ball_x - ball_radius < 0){
        ball_x = ball_radius;
    }
    
    // Check if the ball touches the right wall
    if(ball_x + ball_radius > window_width){
        ball_x = window_width - ball_radius; // Keep the ball within bounds
        gameComplete = true; // Set game as complete
    }

    if(ball_y - ball_radius < 0){
        ball_y = ball_radius;
    }
    if(ball_y + ball_radius > window_height){
        ball_y = window_height - ball_radius;
    }

    UpdateRectangles();
    HandleCollision();
}

void BallGame::Draw(){
    DrawRectangles();
    DrawBall();
}