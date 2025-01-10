#include "../managers/GameplayManager.h" // Include GameplayManager
#include "gameplay_vars.h"
#include "../headers/CommandInterpreter.h"
#include "../headers/globals.h"

bool isCounting;
//bool isSafeMarginTimerOn;
bool isEnemyIpKnown = false;
bool startMiniGamesSequence = false;
bool payloadState = 0;
ProcessStateName pidState;

CommandInterpreter cmdInterpreter(&gameplayManager);
Rectangle healthBar = {screen.x + 30, screen.y + 30, 1117, 40};
Rectangle attackMenu = {screen.x + 30, screen.y + 97, 249, 106};
Rectangle infoPanel = {screen.x + 30, screen.y + 250, 249, 383};
Rectangle exitWindow = {screen.x + ((screen.width) / 2) - 200, screen.y + ((screenHeight) / 2) - 100, 400, 200};
Rectangle botnetIcon = {attackMenu.x + 20, attackMenu.y + 25, 56, 56};
Rectangle ddosIcon = {attackMenu.x + 96, attackMenu.y + 25, 56, 56};
Rectangle mailbombIcon = {attackMenu.x + 172, attackMenu.y + 25, 56, 56};
Rectangle terminalWindow = {screen.x + 312, screen.y + 97, 556, 540};
Rectangle textBox = terminalWindow;

Vector2 iconDescriptionCoorinates = {infoPanel.x + 10, infoPanel.y + 120};
std::vector<std::string> botnetDescription = {
    "BotNet:",
    "Turn computer",
    "into zombie bots",
    "(40% chance)",
    "Bigger botnet",
    "bigger damage."
};

std::vector<std::string> ddosDescription = {
    "DDOS:",
    "Find open ports",
    "(50% chance).",
    "Attack through port",
    "for 10s, dealing",
    "30% HP damage."
};

std::vector<std::string> mailBombDescription = {
    "Mail Bomb:",
    "Find enemy email",
    "(100% chance).",
    "Send email",
    "(20% chance).",
    "Success reduces",
    "firewall by 30%.",
};

