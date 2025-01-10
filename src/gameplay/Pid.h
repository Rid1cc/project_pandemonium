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
    bool idle;
    int displayEnemyIpFrames ;
    void b_DrainRender();
    void s_DrainRender();
    void PortscanRender();
    void DdosRender();
    void MailRender();
    int animationTimer;
    void AtkBotnetRender();
};

#endif // PID_H
