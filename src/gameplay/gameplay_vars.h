#ifndef GAMEPLAY_VARS_H
#define GAMEPLAY_VARS_H

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

#endif // GAMEPLAY_VARS_H