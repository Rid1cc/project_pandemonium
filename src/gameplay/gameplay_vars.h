#ifndef GAMEPLAY_VARS_H
#define GAMEPLAY_VARS_H

#include "raylib.h"
#include <vector>
#include <string>

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
extern std::vector<std::string> botnetDescription;
extern std::vector<std::string> ddosDescription;
extern std::vector<std::string> mailBombDescription;

#endif // GAMEPLAY_VARS_H