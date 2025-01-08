#include "ConnectWiresGame.h"
#include "../headers/globals.h"
#define pairsNum 8
#define pointsNum 16

ConnectWiresRectangle::ConnectWiresRectangle(float x, float y, float width, float height)
    : rect{ x, y, width, height } {
}

void ConnectWiresRectangle::draw(){
    DrawRectangleLinesEx(rect, 1, PURPLE);
}

void ConnectWiresRectangle::update(){
    // Implement if any dynamic behavior is needed
}

ConnectWiresGame::ConnectWiresGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), moveStartPoint(false), moveEndPoint(false),
      inTargetAreaCounter(0),
      startArea(window.x + 30, window.y + 40, 35, window.height - 60),
      endArea(window.x + window.width - 65, window.y + 40, 35, window.height - 60),
      colors{ ORANGE, GREEN, BLUE, BROWN, WHITE },
      points(pointsNum, Vector2{0,0}),
      isPointMovable(pointsNum, false),
      isAtTargetArea(pointsNum, false),
      targetAreas(pointsNum, ConnectWiresRectangle(0,0,0,0)) {
    CreateWires();
}

void ConnectWiresGame::Update() {
    MiniGame::Update(); // Handle dragging
    UpdatePoints();

}

void ConnectWiresGame::Draw() {
    MiniGame::Draw(); // Draw window 
    DrawWires();
}

void ConnectWiresGame::UpdatePoints() {
    Vector2 mousePositionDelta = GetMouseDelta();
    
    /*handle window drag*/
    if (isDragable && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // if window is being dragged
        // update areas coordinates for start-end points && start-end areas
        startArea.rect.x += mousePositionDelta.x;
        startArea.rect.y += mousePositionDelta.y;
        endArea.rect.x += mousePositionDelta.x;
        endArea.rect.y += mousePositionDelta.y;
        
        for(auto &area : targetAreas){
            area.rect.x += mousePositionDelta.x;
            area.rect.y += mousePositionDelta.y;
        }

        for(auto &point : points){
            point.x += mousePositionDelta.x;
            point.y += mousePositionDelta.y;
        }
    }

    /*handle moving the points*/
    for (int i = pointsNum - 1; i >= 0; i--) { // for all points
        
        // check if point should be able to move
        if ((CheckCollisionPointCircle(mousePos, points[i], window.height * 0.034f)) && 
            (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && 
            !IsAnyMovable()) {
            isPointMovable[i] = true;
            //if(debugMode != LOW)TraceLog(LOG_INFO, "point %i is movable", i);
        }

        if (isPointMovable[i]) {
            points[i] = mousePos;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isPointMovable[i] = false;
                //if(debugMode != LOW)TraceLog(LOG_INFO, "point %i is not movable", i);
            }
        }

        /*move points back to their area*/
        if (i % 2 == 0) { // for start area
            points[i].x = std::clamp(points[i].x, startArea.rect.x, startArea.rect.x + startArea.rect.width);
            points[i].y = std::clamp(points[i].y, startArea.rect.y, startArea.rect.y + startArea.rect.height);
        }
        else { // for end area
            points[i].x = std::clamp(points[i].x, endArea.rect.x, endArea.rect.x + endArea.rect.width);
            points[i].y = std::clamp(points[i].y, endArea.rect.y, endArea.rect.y + endArea.rect.height);
        }
        
        if (CheckCollisionCircleRec(points[i], window.height * 0.034f, targetAreas[i].rect)){
            if(!isAtTargetArea[i]) {
                isAtTargetArea[i] = true;
                inTargetAreaCounter++;
                //if(debugMode != LOW)TraceLog(LOG_INFO, "Point %i is in right spot!", i);
            }
        } 
        else {
            if(isAtTargetArea[i]) {
                isAtTargetArea[i] = false;
                inTargetAreaCounter--;
                //if(debugMode != LOW)TraceLog(LOG_INFO, "Point %i is not in right spot!", i);
            }
        }
        
        if (inTargetAreaCounter >= 14 && 
            CheckCollisionCircleRec(points[7], window.height * 0.034f, targetAreas[11].rect) && 
            CheckCollisionCircleRec(points[11], window.height * 0.034f, targetAreas[7].rect)) {
            if(!gameComplete) {
                //if(debugMode != LOW)TraceLog(LOG_INFO, "MiniGame Complete!");
                gameComplete = true;
            }
        }
    }

}

bool ConnectWiresGame::IsAnyMovable() {
    return std::any_of(isPointMovable.begin(), isPointMovable.end(), [](bool movable) { return movable; });
}

void ConnectWiresGame::DrawWires() {
    for (int i = 0; i < pairsNum; i++) {
        if (2*i + 1 >= pointsNum || i >= targetAreas.size()) {
            // Prevent out-of-bounds access
            continue;
        }
        DrawLineBezier(points[2*i], points[(2*i)+1], window.height * 0.015f, (i%2==0) ? colors[i/2] : colors[(i-1)/2]);
        DrawCircleV(points[i*2], CheckCollisionPointCircle(mousePosition, points[i*2], window.height * 0.034f) ? window.height * 0.0467f : window.height * 0.0267f, (i%2==0) ? WHITE : colors[i/2]);
        DrawCircleV(points[(i*2)+1], CheckCollisionPointCircle(mousePosition, points[(i*2)+1], window.height * 0.034f) ? window.height * 0.0467f : window.height * 0.0267f, (i%2==0) ? WHITE : colors[i/2]);
    }
    for (size_t i = 0; i < targetAreas.size(); ++i) {
        // Ensure each area is valid before drawing
        if (i < targetAreas.size()) {
            targetAreas[i].draw();
        }
    }
}

void ConnectWiresGame::CreateWires() {
    for (int i = 0; i < pointsNum; i++) {
        // Initialize points
        if (i % 2 == 0){ // for startArea
            points[i] = { startArea.rect.x + (startArea.rect.width / 2), 
                         startArea.rect.y + (startArea.rect.height / 8) / 2 + (startArea.rect.height / 8) * (i / 2) };
            targetAreas[i] = ConnectWiresRectangle(startArea.rect.x, 
                                                  startArea.rect.y + (startArea.rect.height / 8) * (i / 2), 
                                                  startArea.rect.width, 
                                                  startArea.rect.height / 8);
        }
        else { // for endArea
            points[i] = { endArea.rect.x + (endArea.rect.width / 2), 
                         endArea.rect.y + endArea.rect.height - ((endArea.rect.height / 8) / 2) - (endArea.rect.height / 8) * (i / 2) };
            //if(debugMode != LOW)TraceLog(LOG_INFO, "successfully created pair %i", ((i + 1)/2));
            targetAreas[i] = ConnectWiresRectangle(endArea.rect.x, 
                                                  endArea.rect.y + (endArea.rect.height / 8) * (i / 2), 
                                                  endArea.rect.width, 
                                                  endArea.rect.height / 8);
            //if(debugMode != LOW)TraceLog(LOG_INFO, "successfully created target %i", (i + 1)/2);
        }
        isPointMovable[i] = false;
        isAtTargetArea[i] = false;
    }
}

