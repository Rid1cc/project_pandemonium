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
    } else {
        switch(pidState) {
            case B_DRAIN:
                DrawTextC("DRAINING", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                if(gameplayManager.timer.countdownFrames <= 1){
                    isEnemyIpKnown = true;
                }
                break;
            case S_DRAIN:
                DrawTextC("SILENT DRAIN", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case MAIL:
                DrawTextC("MAIL", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case DDOS:
                DrawTextC("DDOS", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case ADD_BOTNET:
                DrawTextC("ADD BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            case ATK_BOTNET:
                DrawTextC("ATTACK BOTNET", pidMenu.x + 20, pidMenu.y + (pidMenu.height/2), 40, primaryColor);
                break;
            default:
                break;
        }
    }
    DrawRectangleLinesEx(pidMenu, 2, primaryColor);
}
