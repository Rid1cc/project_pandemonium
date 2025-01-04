#include "../managers/GameplayManager.h" // Include GameplayManager
#include "gameplay_vars.h"
#include "../headers/CommandInterpreter.h"
#include "../headers/globals.h"

bool isCounting;
bool isEnemyIpKnown = true;
ProcessStateName pidState;

CommandInterpreter cmdInterpreter(&gameplayManager);
Rectangle healthBar = {screen.x + 30, screen.y + 30, 1117, 40};
Rectangle attackMenu = {screen.x + 30, screen.y + 97, 249, 106};
Rectangle infoPanel = {screen.x + 30, screen.y + 250, 249, 383};
Rectangle botnetIcon = {attackMenu.x + 20, attackMenu.y + 25, 56, 56};
Rectangle ddosIcon = {attackMenu.x + 96, attackMenu.y + 25, 56, 56};
Rectangle mailbombIcon = {attackMenu.x + 172, attackMenu.y + 25, 56, 56};
Rectangle terminalWindow = {screen.x + 312, screen.y + 97, 556, 540};
Rectangle textBox = terminalWindow;

Vector2 iconDescriptionCoorinates = {infoPanel.x + 10, infoPanel.y + 120};
std::string botnetDescription = "BotNet:\nTurn computer \ninto zombie bots\n(40% chance)\nBigger botnet,\nbigger damage.";
std::string ddosDescription = "DDOS:\nFind open ports\n(50% chance).\nAttack through port\nfor 10s, dealing\n30% HP damage.";
std::string mailBombDescription = "Mail Bomb:\nFind enemy email\n(100% chance).\nSend email \n(20% chance).\nSuccess reduces \nfirewall\nby 30%.";
