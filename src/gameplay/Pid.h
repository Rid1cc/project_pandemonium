#ifndef PID_H
#define PID_H

#include "raylib.h"

class Pid {
public:
    Pid();
    void RenderIdle();
    void Render();
private:
    Rectangle pidMenu;
    void RenderIcons();
    bool idle;
};

#endif // PID_H
