#include "FinderGame.h"

FinderGame::FinderGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title), scissorMode(true){
        // setting scissor Area to follow window
        // scissorArea = window;
}


void FinderGame::Update() {
    MiniGame::Update(); // Hangle dragging 
    
    // switch scissor mode (key 'S')
    if (IsKeyPressed(KEY_S)) {
        scissorMode = !scissorMode;
    }

    scissorArea = window;
}

void FinderGame::Draw() {
    MiniGame::Draw(); // draw window


    if (scissorMode) {
        BeginScissorMode((int)scissorArea.x, (int)scissorArea.y, (int)scissorArea.width, (int)scissorArea.height);
    } // Begin Scissor Mode 

    DrawText("TESTOWY TEKST ODKRYWANY MYSZKA",  20, 60, 20, WHITE);

    if (scissorMode) {
        EndScissorMode();
    }
}
