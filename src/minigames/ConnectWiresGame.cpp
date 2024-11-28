#include "ConnectWiresGame.h"

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), 
    startPoint({30, 30}),
    mouse(GetMousePosition()),
    moveStartPoint(false), 
    moveEndPoint(false) {
    endPoint = {window.x - 30, window.y - 30};
}   


void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    Vector2 mouse = GetMousePosition();


    // moving balls
    if (CheckCollisionPointCircle(mouse, startPoint, 10.0f) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveStartPoint = true;
    else if (CheckCollisionPointCircle(mouse, endPoint, 10.0f) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) moveEndPoint = true;

    if (moveStartPoint)
    {
        startPoint = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveStartPoint = false;
    }

    if (moveEndPoint)
    {
        endPoint = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveEndPoint = false;
    }
}

void ConnectWiresGame::Draw() {
    MiniGame::Draw(); // Draw window
    // Draw line Cubic Bezier, in-out interpolation (easing), no control points
    DrawLineBezier(startPoint, endPoint, 4.0f, BLUE);
            
    // Draw start-end spline circles with some details
    DrawCircleV(startPoint, CheckCollisionPointCircle(mouse, startPoint, 10.0f)? 14.0f : 8.0f, moveStartPoint? RED : BLUE);
    DrawCircleV(endPoint, CheckCollisionPointCircle(mouse, endPoint, 10.0f)? 14.0f : 8.0f, moveEndPoint? RED : BLUE);
}