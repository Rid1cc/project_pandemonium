#ifndef LITWA_MINIGRA1_H
#define LITWA_MINIGRA1_H

#include "../headers/MiniGameManager.h"

class AxeGame : public MiniGame {
private:
    float rotation; // Rectangle rotation
    Rectangle rectInner; // Inner rectangle to rotate

public:
    RotatingRectangleGame(float x, float y, float width, float height, const std::string& title);

    void Update() override;
    void Draw() override;
};

#endif // ROTATING_RECTANGLE_GAME_H
