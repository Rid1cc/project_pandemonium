#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "raylib.h"
#include <vector>
#include <string>

class InfoPanel {
public:
    InfoPanel();
    void Render();
private:
    void DrawIconDescription(std::vector<std::string> iconDescription, Vector2 iconDescriptionStartingPoint);

};

#endif // PID_H
