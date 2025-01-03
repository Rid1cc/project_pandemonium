#ifndef GAMEPLAY_VARS_H
#define GAMEPLAY_VARS_H

#include "raylib.h"

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

extern Rectangle healthBar;
extern Rectangle attackMenu;
extern Rectangle infoPanel;
extern Rectangle terminalWindow;
extern Rectangle PIDMenu;
extern Rectangle textBox;
extern Rectangle botnetIcon;
extern Rectangle ddosIcon;
extern Rectangle mailbombIcon;

extern Vector2 iconDescriptionCoorinates;
extern std::string botnetDescription;
extern std::string ddosDescription;
extern std::string mailBombDescription;

#endif // GAMEPLAY_VARS_H