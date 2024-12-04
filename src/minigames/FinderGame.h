#ifndef FINDER_GAME_H
#define FINDER_GAME_H

#include "../headers/MiniGameManager.h"

class FinderGame : public MiniGame {
private:
    Rectangle scissorArea; // 
    bool scissorMode; // 
public:
    FinderGame(float x, float y, float width, float height, const std::string& title);

    void Update() override;
    void Draw() override;
};


#endif // FINDER_H