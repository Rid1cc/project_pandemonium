#include "ConnectWiresGame.h"
#include "../headers/globals.h"
#define pairsNum 8
#define pointsNum 16

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), moveStartPoint(false), moveEndPoint(false),
    mousePosition(mousePos), points(), isPointMovable(), targetAreas(), isAtTargetArea(), inTargetAreaCounter() {
    startArea = {window.x + 30, window.y + 40, 35, window.height - 60};
    endArea = {window.x + window.width - 65, window.y + 40, 35, window.height - 60};
    colors = {ORANGE, GREEN, BLUE, BROWN, WHITE};
    CreateWires();
}


void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    // if (manager->onTop == GetThis()) {
    // } 
        UpdatePoints();
}


void ConnectWiresGame::Draw() {
    MiniGame::Draw(); // Draw window 
    DrawWires();
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

    /*handle moving the points*/
    for (int i = pointsNum - 1; i >= 0; i--) { // for all points
        
        // Drag points with window
        if (isDragable && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        points[i].x += mousePositionDelta.x;
        points[i].y += mousePositionDelta.y;
        targetAreas[i].x += mousePositionDelta.x;
        targetAreas[i].y += mousePositionDelta.y;
        }

        // check if point should be able to move
        if ((CheckCollisionPointCircle(mousePos, points[i], 10.0f)) && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && !IsAnyMovable()) {
            isPointMovable[i] = true;
            TraceLog(LOG_INFO, "point %i is movable", i);
        }
        if (isPointMovable[i]) {
            points[i] = mousePos;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isPointMovable[i] = false;
                TraceLog(LOG_INFO, "point %i is not movable", i);
            }
        }

        /*move points back to their area*/
        if (i % 2 == 0) { // for start area
            if ((points[i].x >= (startArea.x + startArea.width))) points[i].x = startArea.x + startArea.width;
            else if (points[i].x <= (startArea.x)) points[i].x = startArea.x;
            if (points[i].y >= (startArea.y + startArea.height)) points[i].y = startArea.y + startArea.height;
            else if (points[i].y <= startArea.y) points[i].y = startArea.y;
        }
        else {
            if ((points[i].x >= (endArea.x + endArea.width))) points[i].x = endArea.x + endArea.width;
            else if (points[i].x <= (endArea.x)) points[i].x = endArea.x;
            if (points[i].y >= (endArea.y + endArea.height)) points[i].y = endArea.y + endArea.height;
            else if (points[i].y <= endArea.y) points[i].y = endArea.y;
        }
    
        
        if (CheckCollisionCircleRec(points[i], 10.0f, targetAreas[i])){
            if(isAtTargetArea[i] == false) {
                isAtTargetArea[i] = true;
                inTargetAreaCounter++;
                TraceLog(LOG_INFO, "Point %i is in right spot!", i);
            }
        } 
        else if(!CheckCollisionCircleRec(points[i], 10.0f, targetAreas[i])) {
            if(isAtTargetArea[i] == true) {
                isAtTargetArea[i] = false;
                inTargetAreaCounter--;
                TraceLog(LOG_INFO, "Point %i is not in right spot!", i);
            }
        }
        
        if (inTargetAreaCounter == 14 && CheckCollisionCircleRec(points[7], 10.0f, targetAreas[11]) && CheckCollisionCircleRec(points[11], 10.0f, targetAreas[7])) {
            if(!gameComplete) {
            TraceLog(LOG_INFO, "MiniGame Complete!");
            gameComplete = true;
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
        DrawCircleV(points[i*2], CheckCollisionPointCircle(mousePosition, points[i*2], 10.0f)? 14.0f : 8.0f,(i%2==0)? WHITE:colors[i/2]);
        DrawCircleV(points[(i*2)+1], CheckCollisionPointCircle(mousePosition, points[(i*2)+1], 10.0f)? 14.0f : 8.0f,(i%2==0)? WHITE:colors[i/2]);
    }
    for (int i = 0; i < pointsNum; i++) {
        DrawRectangleLinesEx(targetAreas[i], 1, PURPLE);
    }
}


void ConnectWiresGame::CreateWires() {
    points.reserve(pointsNum);
    isPointMovable.reserve(pointsNum);
    targetAreas.reserve(pointsNum);
    isAtTargetArea.reserve(pointsNum);
    for (int i = 0; i < pointsNum; i++) {
        // set points to not movable
        isPointMovable[i] = false;
        isAtTargetArea[i] = false;
        if (i % 2 == 0){ // for startArea
            // set points (x, y)
            points[i] = {startArea.x + (startArea.width/2), startArea.y + (startArea.height/8)/2 + (startArea.height/8)*(i/2)};
            // set targetAreas
            targetAreas[i] = {startArea.x, startArea.y + (startArea.height/8)*(i/2), startArea.width, (startArea.height/8)};}
        else if (i % 2 == 1) { // for endArea
            // set points (x, y)
            points[i] = {endArea.x + (endArea.width/2), endArea.y + endArea.height - ((endArea.height/8)/2) - (startArea.height/8)*(i/2)};
            TraceLog(LOG_INFO, "succesfully created pair %i", ((i + 1)/2));
            // set targetAreas
            targetAreas[i] = {endArea.x,endArea.y + (endArea.height/8)*(i/2),endArea.width, (endArea.height/8)};
            TraceLog(LOG_INFO, "successfully created target %i", (i + 1)/2);
        }
    }
}

