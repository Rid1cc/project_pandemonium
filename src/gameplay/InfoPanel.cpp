#include "InfoPanel.h"
#include "../headers/globals.h"
#include "../managers/GameplayManager.h"
#include "gameplay_vars.h"

// Constructor to initialize PID menu properties
InfoPanel::InfoPanel() {
    //infoPanel = {screen.x + 30, screen.y + 250, 249, 383};
}


void InfoPanel::Render() {
    DrawRectangleLinesEx(infoPanel, 2, primaryColor);
    DrawTextC("Daemon name: ", infoPanel.x + 10, infoPanel.y + 20, 20, primaryColor);
    DrawTextC(gameplayManager.enemyHostname.c_str(), infoPanel.x + 10, infoPanel.y + 40, 20, primaryColor);
    DrawTextC("Daemon IP: ", infoPanel.x + 10, infoPanel.y + 70, 20, primaryColor);
    if(isEnemyIpKnown)
        DrawTextC(gameplayManager.enemyIp.c_str(), infoPanel.x + 10, infoPanel.y + 90, 20, primaryColor);
    else 
        DrawTextC("Unknown", infoPanel.x + 10, infoPanel.y + 90, 20, primaryColor);
    
    if (!miniGamesManager.CheckMouseState()) {
        if (CheckCollisionPointRec(mousePos, botnetIcon))
            DrawTextC(botnetDescription.c_str(), iconDescriptionCoorinates.x, iconDescriptionCoorinates.y, 20, primaryColor);
        else if (CheckCollisionPointRec(mousePos, ddosIcon))
            DrawTextC(ddosDescription.c_str(), iconDescriptionCoorinates.x, iconDescriptionCoorinates.y, 20, primaryColor);
        else if (CheckCollisionPointRec(mousePos, mailbombIcon))
            DrawTextC(mailBombDescription.c_str(), iconDescriptionCoorinates.x, iconDescriptionCoorinates.y, 20, primaryColor);
    }
}