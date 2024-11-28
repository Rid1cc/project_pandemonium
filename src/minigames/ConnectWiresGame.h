#ifndef CONNECT_WIRES_GAME_H
#define CONNECT_WIRES_GAME_H

#include "../headers/MiniGameManager.h"

class ConnectWiresGame : public MiniGame
{
private:
    Vector2 startPoint;
    Vector2 mouse;
    bool moveStartPoint;
    bool moveEndPoint;
    Vector2 endPoint;

public:
    // constructor
    ConnectWiresGame(float x, float y, float width, float height, const std::string& title);
    ~ConnectWiresGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // CONNECT_WIRES_GAME_H