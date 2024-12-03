#include "ConnectWiresGame.h"

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), mouse(GetMousePosition()), moveStartPoint(false), moveEndPoint(false) {
    // wirePoints.at(0).at(0) = {window.x + 30, window.y + 60};
    // wirePoints.at(0).at(1) = {window.x + window.width - 30, window.y + window.height - 30};
    startPoint = {window.x + 30, window.y + 60};
    endPoint = {window.x + window.width - 30, window.y + window.height - 35};
    startArea = {window.x + 30, window.y + 40, 35, window.height - 60};
    endArea = {window.x + window.width - 65, window.y + 40, 35, window.height - 60};
    
    createWirePoints(wirePoints);
}


void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    Vector2 mouse = GetMousePosition();

    DragObjects(startArea, endArea, wirePoints[0], wirePoints[1], isDragable);
    MoveToArea(wirePoints[0], startArea);
    MoveToArea(wirePoints[1], endArea);

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
    //test rectangle for starting points
    DrawRectangleLinesEx({window.x + 30, window.y + 40, 35, window.height - 60}, 2, WHITE);
    //test rectangle for ending points
    DrawRectangleLinesEx({window.x + window.width - 65, window.y + 40, 35, window.height - 60}, 2, WHITE);


    // connecting line
    DrawLineBezier(wirePoints[0], wirePoints[1], 4.0f, (Color) {255, 161, 0, 255});

    // Draw start-end spline circles with some details
    DrawCircleV(wirePoints[0], CheckCollisionPointCircle(mouse, wirePoints[0], 10.0f)? 14.0f : 8.0f, moveStartPoint? ORANGE : WHITE);
    //MoveToArea(wirePoints[0], startArea); // move startPoint to startArea
    DrawCircleV(wirePoints[1], CheckCollisionPointCircle(mouse, wirePoints[1], 10.0f)? 14.0f : 8.0f, moveEndPoint? ORANGE : WHITE);
    //MoveToArea(wirePoints[1], endArea); // move endPoint to endArea
}


void ConnectWiresGame::createWirePoints(std::vector<Vector2>& points) {
    int points_num = 16;
    points.reserve(points_num);
    for (int i = 0; i < points_num; i++) {
        if (i % 2 == 0)
            points[i] = {startArea.x + (startArea.width/2), startArea.y + ((i / 2) + 1)*(startArea.height/8)/2};
        else if (i % 2 == 1) {
            points[i] = {endArea.x + (endArea.width/2), endArea.y + endArea.height - ((i + 1)/2)*(endArea.height/8)/2};
            TraceLog(LOG_INFO, "succesfully created pair %i", ((i + 1)/2));}
    }
}



void ConnectWiresGame::MoveToArea(Vector2& point, Rectangle& area)  {
    if ((point.x) >= (area.x + area.width)) 
        point.x = area.x + (area.width/2);
    else if (point.x <= (area.x))
        point.x = area.x + (area.width/2);
    else if (point.y >= area.y + area.height) 
        point.y = area.y + area.height - 1;
    else if (point.y <= area.y) 
        point.y = area.y + 1;
}


void ConnectWiresGame::DragObjects(Rectangle& startArea, Rectangle& endArea, Vector2& startpoint, Vector2& endpoint, bool& isDragable){
    if (isDragable) { // if window is beeing dragged
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // update areas coordinates for start/end points
            Vector2 mouseDelta = GetMouseDelta();
            startArea.x += mouseDelta.x;
            startpoint.x += mouseDelta.x;
            startArea.y += mouseDelta.y;
            startpoint.y += mouseDelta.y;
            endArea.x += mouseDelta.x;
            endpoint.x += mouseDelta.x;
            endArea.y += mouseDelta.y;
            endpoint.y += mouseDelta.y;

        }
    }
}






