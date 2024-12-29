#ifndef CONNECT_WIRES_GAME_H
#define CONNECT_WIRES_GAME_H

#include "../headers/MiniGameManager.h"
#include <vector>

class ConnectWiresRectangle {
public:
    Rectangle rect;
    // Additional properties if needed

    ConnectWiresRectangle(float x, float y, float width, float height);
    void draw();
    void update();
};

class ConnectWiresGame : public MiniGame
{
private:
    bool moveStartPoint;
    bool moveEndPoint;
    
    int inTargetAreaCounter;
    Vector2 mousePosition;
    ConnectWiresRectangle startArea;
    ConnectWiresRectangle endArea;
    std::vector<ConnectWiresRectangle> targetAreas;
    std::vector<Color> colors; // 4 colors (orange, green, blue, brown, white)
    std::vector<Vector2> points;
    std::vector<bool> isPointMovable;
    std::vector<bool> isAtTargetArea;
    void DrawWires();
    bool IsAnyMovable();
    void UpdatePoints();
    void CreateWires();

public:
    // constructor
    ConnectWiresGame(float x, float y, float width, float height, const std::string& title);
    // standard destructor
    ~ConnectWiresGame() = default;


    void Update() override;
    void Draw() override;
};

#endif // CONNECT_WIRES_GAME_H