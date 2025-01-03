#include "../managers/GameplayManager.h" // Include GameplayManager
#include "gameplay_vars.h"
#include "../headers/globals.h"

bool isCounting;
bool isEnemyIpKnown = false;
ProcessStateName pidState;

Rectangle healthBar = {screen.x + 30, screen.y + 30, 1117, 40};
Rectangle attackMenu = {screen.x + 30, screen.y + 97, 249, 106};
Rectangle botnetIcon = {attackMenu.x + 20, attackMenu.y + 25, 56, 56};
Rectangle ddosIcon = {attackMenu.x + 96, attackMenu.y + 25, 56, 56};
Rectangle mailbombIcon = {attackMenu.x + 172, attackMenu.y + 25, 56, 56};
Rectangle terminalWindow = {screen.x + 312, screen.y + 97, 556, 540};
Rectangle textBox = terminalWindow;