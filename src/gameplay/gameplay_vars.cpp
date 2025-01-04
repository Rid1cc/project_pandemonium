#include "../managers/GameplayManager.h" // Include GameplayManager
#include "gameplay_vars.h"
#include "../headers/CommandInterpreter.h"
#include "../headers/globals.h"

bool isCounting;
bool isEnemyIpKnown = false;
ProcessStateName pidState;

CommandInterpreter cmdInterpreter(&gameplayManager);