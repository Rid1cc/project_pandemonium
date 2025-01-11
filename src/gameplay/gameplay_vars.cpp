#include "../managers/GameplayManager.h" // Include GameplayManager
#include "gameplay_vars.h"
#include "../headers/CommandInterpreter.h"
#include "../headers/globals.h"

bool isPIDCounting;
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
    "Build botnet with",
    "cilents in network",
    "(command: botnet)",
    "attack has 40%",
    "chance of success"
};

std::vector<std::string> ddosDescription = {
    "FLOOD:",
    "Flood enemy IP",
    "through port.",
    "(command: flood)",
    "(needed: port)",
    "(needed: ip address)"
};

std::vector<std::string> mailBombDescription = {
    "Mail Bomb:",
    "Send malicious",
    "email to enemy.",
    "(command: smtp)",
    "(20% chance).",
};

