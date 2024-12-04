#ifndef CONNECT_WIRES_GAME_H
#define CONNECT_WIRES_GAME_H

#include "../headers/MiniGameManager.h"
#include <vector>
#include <memory>

class ConnectWiresGame : public MiniGame
{
private:
    bool moveStartPoint;
    bool moveEndPoint;
    std::vector<bool> isPointMovable;
    Vector2 mousePosition;
    Rectangle startArea;
    Rectangle endArea;
    std::vector<Color> colors; // 4 colors (orange, green, blue, brown, white)
    std::vector<Vector2> points;
    void DrawWires();
    void MovePoints();
    bool IsAnyMovable();
    void UpdatePoints();
    void CreateWires();
    // void MovePointsToArea();
    void DragObjectsWithWindow();

public:
    // constructor
    ConnectWiresGame(float x, float y, float width, float height, const std::string& title);
    // standard destructor
    ~ConnectWiresGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // CONNECT_WIRES_GAME_H