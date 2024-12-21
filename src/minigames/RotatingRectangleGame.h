#ifndef ROTATING_RECTANGLE_GAME_H
#define ROTATING_RECTANGLE_GAME_H

#include "../headers/MiniGameManager.h"

class RotatingRectangleGame : public MiniGame {
private:
    float rotation; // Rectangle rotation
    Rectangle rectInner; // Inner rectangle to rotate

public:
    RotatingRectangleGame(float x, float y, float width, float height, const std::string& title);
    ~RotatingRectangleGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // ROTATING_RECTANGLE_GAME_H
