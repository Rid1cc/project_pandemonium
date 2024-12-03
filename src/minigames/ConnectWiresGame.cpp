#include "ConnectWiresGame.h"

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), mouse(GetMousePosition()), moveStartPoint(false), moveEndPoint(false) {
    startPoint = {window.x + 30, window.y + 60};
    endPoint = {window.x + window.width - 30, window.y + window.height - 30};
    startArea = {window.x + 30, window.y + 40, 35, window.height - 60};
    endArea = {window.x + window.width - 65, window.y + 40, 35, window.height - 60};
}   

void MoveToArea(Vector2& point, Rectangle& area);
void DragAreas(Rectangle& startArea, Rectangle& endArea, bool& isDragable);

void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    Vector2 mouse = GetMousePosition();

    DragAreas(startArea, endArea, isDragable);
    MoveToArea(startPoint, startArea);
    MoveToArea(endPoint, endArea);

    // moving balls
    if (CheckCollisionPointCircle(mouse, startPoint, 10.0f) /*&& CheckCollisionPointRec(startPoint, startArea)*/ && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (isDragable && !CheckCollisionPointCircle(mouse, startPoint, 10.0f)))) moveStartPoint = true;
    else if (CheckCollisionPointCircle(mouse, endPoint, 10.0f) /*&& CheckCollisionPointRec(endPoint, endArea)*/ && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) moveEndPoint = true;

    if (moveStartPoint) {
        startPoint = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveStartPoint = false;
    }

    if (moveEndPoint) {
        endPoint = mouse;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) moveEndPoint = false;
    }
}


void ConnectWiresGame::Draw() {
    MiniGame::Draw(); // Draw window


    DrawLineBezier(startPoint, endPoint, 4.0f, (Color) {255, 161, 0, 255});

    //test rectangle for starting points
    DrawRectangleLinesEx({window.x + 30, window.y + 40, 35, window.height - 60}, 2, WHITE);

    //test rectangle for ending points
    DrawRectangleLinesEx({window.x + window.width - 65, window.y + 40, 35, window.height - 60}, 2, WHITE);

    // Draw start-end spline circles with some details
    DrawCircleV(startPoint, CheckCollisionPointCircle(mouse, startPoint, 10.0f)? 14.0f : 8.0f, moveStartPoint? ORANGE : WHITE);
    MoveToArea(startPoint, startArea); // move startPoint to startArea
    DrawCircleV(endPoint, CheckCollisionPointCircle(mouse, endPoint, 10.0f)? 14.0f : 8.0f, moveEndPoint? ORANGE : WHITE);
    MoveToArea(endPoint, endArea); // move endPoint to endArea
}

void MoveToArea(Vector2& point, Rectangle& area) {
    if ((point.x) >= (area.x + area.width)) point.x = area.x + (area.width/2);
    else if (point.x <= (area.x)) point.x = area.x + (area.width/2);
    else if (point.y >= area.y + area.height) point.y = area.y + area.height - 1;
    else if (point.y <= area.y) point.y = area.y + 1;
}

void DragAreas(Rectangle& startArea, Rectangle& endArea, bool& isDragable){
    if (isDragable) { // if window is beeing dragged
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // update areas coordinates for start/end points
            Vector2 mouseDelta = GetMouseDelta();
            startArea.x += mouseDelta.x;
            startArea.y += mouseDelta.y;
            endArea.x += mouseDelta.x;
            endArea.y += mouseDelta.y;
        }
    }
}