#ifndef TYPE_GAME_H
#define TYPE_GAME_H

#include "../headers/MiniGameManager.h"
#include "../headers/globals.h"

class TypeGame: public MiniGame {
private:

public:
    TypeGame(float x, float y, float width, float height, const std::string& title);
    // bool isTypeWin;
    void Update() override;
    void Draw() override;
};

#endif 