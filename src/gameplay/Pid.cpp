#include "Pid.h"
#include "../headers/globals.h"
#include "gameplay_vars.h"

// Constructor to initialize PID menu properties
Pid::Pid() {
    pidMenu = {screen.x + 900, screen.y + 97, 249, 540};
    idle = true;
}

// Render the PID menu
void Pid::RenderIdle() {
    DrawRectangleRec(pidMenu, BLACK);
    DrawTextC("NO", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) - 50, 40, primaryColor);
    DrawTextC("PROCESS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
    DrawTextC("ACTIVE", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2) + 50, 40, primaryColor);
}

void Pid::Render() {
    // Debug: Check timer status
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
