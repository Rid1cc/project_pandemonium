#ifndef GAMEPLAY_VARS_H
#define GAMEPLAY_VARS_H

#include "../headers/CommandInterpreter.h"

typedef enum ProcessStateName {
    NONE_P = 0,
    B_DRAIN,
    S_DRAIN,
    MAIL,
    DDOS,
    ADD_BOTNET,
    ATK_BOTNET
} ProcessStateName;
extern bool isCounting;
extern bool isEnemyIpKnown;
extern ProcessStateName pidState;
extern CommandInterpreter cmdInterpreter;

#endif // GAMEPLAY_VARS_H