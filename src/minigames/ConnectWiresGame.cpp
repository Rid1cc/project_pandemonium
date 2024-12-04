#include "ConnectWiresGame.h"
#define pairsNum 8
#define pointsNum 16

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), moveStartPoint(false), moveEndPoint(false), 
    mousePosition(GetMousePosition()), points(), isPointMovable() {
    startArea = {window.x + 30, window.y + 40, 35, window.height - 60};
    endArea = {window.x + window.width - 65, window.y + 40, 35, window.height - 60};
    colors = {ORANGE, GREEN, BLUE, BROWN, WHITE};
    CreateWires();
}


void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    Vector2 mousePosition = GetMousePosition();

    UpdatePoints();

    // DragObjectsWithWindow();
    // MovePoints();
    // MovePointsToArea();

    

}


void ConnectWiresGame::Draw() {
    MiniGame::Draw(); // Draw window 
    DrawWires();

    DrawRectangleLinesEx({window.x + 30, window.y + 40, 35, window.height - 60}, 2, WHITE);
    DrawRectangleLinesEx({window.x + window.width - 65, window.y + 40, 35, window.height - 60}, 2, WHITE);

}


void ConnectWiresGame::UpdatePoints() {
    Vector2 mousePositionDelta = GetMouseDelta();
    /*handle window drag*/
        if (isDragable && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // if window is beeing dragged
            // update areas coordinates for start-end points && start-end areas
            startArea.x += mousePositionDelta.x;
            startArea.y += mousePositionDelta.y;
            endArea.x += mousePositionDelta.x;
            endArea.y += mousePositionDelta.y;
        }

    /*handle moving points*/
    for (int i = (pointsNum -1); i >= 0; i--) { // for all points
        
        // Drag points with window
        if (isDragable && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        points[i].x += mousePositionDelta.x;
        points[i].y += mousePositionDelta.y;
        }

        // check if point should be able to move
        if ((CheckCollisionPointCircle(GetMousePosition(), points[i], 10.0f)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !IsAnyMovable()) {
            isPointMovable[i] = true;
            TraceLog(LOG_INFO, "point %i is movable", i);
        }
        if (isPointMovable[i]) {
            points[i] = GetMousePosition();
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isPointMovable[i] = false;
                TraceLog(LOG_INFO, "point %i is not movable", i);
            }
        }

        /*move points back to their area*/
        if (i % 2 == 0) { // for start area
            if ((points[i].x >= (startArea.x + startArea.width)) || points[i].x <= (startArea.x))
                points[i].x = startArea.x + (startArea.width/2);
            else if (points[i].y >= (startArea.y + startArea.height))
                points[i].y = startArea.y + startArea.height - 10;
            else if (points[i].y <= startArea.y)
                points[i].y = startArea.y + 10;
        }
        else {
            if ((points[i].x >= (endArea.x + endArea.width)) || points[i].x <= (endArea.x))
                points[i].x = endArea.x + (endArea.width/2);
            else if (points[i].y >= (endArea.y + endArea.height))
                points[i].y = endArea.y + endArea.height - 10;
            else if (points[i].y <= endArea.y)
                points[i].y = endArea.y + 10;
        }
    }

}


void ConnectWiresGame::MovePoints() {
    // check if point should be able to move
    for (int i = (pointsNum -1); i >= 0; i--) {
        // for all points
        if ((CheckCollisionPointCircle(GetMousePosition(), points[i], 10.0f)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !IsAnyMovable()) {
            isPointMovable[i] = true;
            TraceLog(LOG_INFO, "point %i is movable", i);
        }
        if (isPointMovable[i]) {
            points[i] = GetMousePosition();
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isPointMovable[i] = false;
                TraceLog(LOG_INFO, "point %i is not movable", i);
            }
        }
    }
}


bool ConnectWiresGame::IsAnyMovable() {
    for (int i = 0; i < pointsNum; i++) {
        if (isPointMovable[i] == true) return true;
    }
    return false;
}


void ConnectWiresGame::DrawWires() {
    // DrawLineBezier(wirePoints[0], wirePoints[1], 4.0f, ORANGE);
    for (int i = 0; i < pairsNum; i++) {
        DrawLineBezier(points[2*i], points[(2*i)+1], 4.0f,(i%2==0)? colors[i/2]:colors[(i-1)/2]);
        DrawCircleV(points[i*2], CheckCollisionPointCircle(mousePosition, points[i*2], 10.0f)? 14.0f : 8.0f,(i%2==0)? colors[i/2]:WHITE);
        DrawCircleV(points[(i*2)+1], CheckCollisionPointCircle(mousePosition, points[(i*2)+1], 10.0f)? 14.0f : 8.0f,(i%2==0)? colors[i/2]:WHITE);
    }
}


void ConnectWiresGame::CreateWires() {
    points.reserve(pointsNum);
    isPointMovable.reserve(pointsNum);
    for (int i = 0; i < pointsNum; i++) {
        isPointMovable[i] = false;
        if (i % 2 == 0) // for points in startArea
            points[i] = {startArea.x + (startArea.width/2), startArea.y + (startArea.height/8)/2 + (startArea.height/8)*(i/2)};
        else if (i % 2 == 1) { // for points in endArea
            points[i] = {endArea.x + (endArea.width/2), endArea.y + endArea.height - ((endArea.height/8)/2) - (startArea.height/8)*(i/2)};
            TraceLog(LOG_INFO, "succesfully created pair %i", ((i + 1)/2));}
    }
}


/*
void ConnectWiresGame::MovePointsToArea()  {
    

    if ((point.x) >= (area.x + area.width)) 
        point.x = area.x + (area.width/2);
    else if (point.x <= (area.x))
        point.x = area.x + (area.width/2);
    else if (point.y >= area.y + area.height) 
        point.y = area.y + area.height - 1;
    else if (point.y <= area.y) 
        point.y = area.y + 1;
}*/


void ConnectWiresGame::DragObjectsWithWindow(){
    if (isDragable) { // if window is beeing dragged
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            // update areas coordinates for start-end points && start-end areas
            Vector2 mousePositionDelta = GetMouseDelta();
            startArea.x += mousePositionDelta.x;
            startArea.y += mousePositionDelta.y;
            endArea.x += mousePositionDelta.x;
            endArea.y += mousePositionDelta.y;
            for (int i = 0; i < pointsNum; i++) {
                points[i].x += mousePositionDelta.x;
                points[i].y += mousePositionDelta.y;
            } 
        }
    }
}

