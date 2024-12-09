#include "TypeGame.h"

TypeGame::TypeGame(float x, float y, float width, float height, const std::string& title)
    : MiniGame(x, y, width, height, title) {
}

void TypeGame::Update(){
    MiniGame::Update();
}

void TypeGame::Draw(){
    MiniGame::Draw();
}