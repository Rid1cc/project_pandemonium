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
    Vector2 mouse;
    Vector2 startPoint;
    Vector2 endPoint;
    Rectangle startArea;
    Rectangle endArea;
    std::vector<Vector2> wirePoints;
    void createWirePoints(std::vector<Vector2>& points);
    void MoveToArea(Vector2& point, Rectangle& area);
    void DragObjects(Rectangle& startArea, Rectangle& endArea, Vector2& startpoint, Vector2& endpoint, bool& isDragable);

public:
    // constructor
    ConnectWiresGame(float x, float y, float width, float height, const std::string& title);
    // standard destructor
    ~ConnectWiresGame() = default;

    void Update() override;
    void Draw() override;
};

#endif // CONNECT_WIRES_GAME_H