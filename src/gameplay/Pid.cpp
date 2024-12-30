#include "Pid.h"
#include "../headers/globals.h"

// Constructor to initialize PID menu properties
Pid::Pid() {
    pidMenu = {screen.x + 900, screen.y + 97, 249, 540};
    idle = true;
}

// Render the PID menu
void Pid::RenderIdle() {
    DrawRectangleRec(pidMenu, BLACK);
    DrawText("NO", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) - 50, 40, WHITE);
    DrawText("PROCESS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, WHITE);
    DrawText("ACTIVE", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) + 50, 40, WHITE);
}

void Pid::Render() {
    // Debug: Check timer status
    bool isCounting = gameplayManager.timer.isCounting();
    
    if(!isCounting) {
        RenderIdle();
        DrawRectangleLinesEx(pidMenu, 2, primaryColor);
    } else {
        DrawRectangleRec(pidMenu, BLACK);
        DrawText("PID", pidMenu.x + 20, (pidMenu.height/2) - 50, 40, WHITE);
        DrawText("PROCESS", pidMenu.x + 20, (pidMenu.height/2), 40, WHITE);
        DrawText("MANAGER", pidMenu.x + 20, (pidMenu.height/2) + 50, 40, WHITE);
        DrawRectangleLinesEx(pidMenu, 2, primaryColor);
    }
}

// Render icons within the PID menu
void Pid::RenderIcons() {
    // Icon 1
    DrawRectangle(pidMenu.x + 20, pidMenu.y + 25, 56, 56, primaryColor);
    // Icon 2
    DrawRectangle(pidMenu.x + 96, pidMenu.y + 25, 56, 56, primaryColor);
    // Icon 3
    DrawRectangle(pidMenu.x + 172, pidMenu.y + 25, 56, 56, primaryColor);
}
