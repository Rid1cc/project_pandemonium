#ifndef FINDER_GAME_H
#define FINDER_GAME_H

#include "../headers/MiniGameManager.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "../headers/globals.h"

class FinderGame : public MiniGame {
private:
    enum GameState {
        MENU,
        GAMEPLAY,
        END
    }; //state of game
    GameState currentScreen;

    Rectangle panel;
    Rectangle startButton;

    Rectangle scissorArea; // scissorArea = Area, where text is visible
    bool scissorMode; // can be delete in the future 
    
    // popping texts 
    std::vector<std::string> goodObjects;
    std::vector<std::string> badObjects;

    struct RandomObject {
        std::string text;
        int x, y;
    }; 
    RandomObject good; // bad text
    RandomObject bad; // good text 

    int timer;
    float lastUpdateTime;
    float currentTime;
    int collected;
    double endScreenStartTime;

    std::string timerText;
    std::string collectedText;


    void DrawStartScreen(); // draw instruction and start button
    void StartButton(); // start button click
    void GenerateRandomObjects(); // generate good and bad X,Y and texts
    bool checkCollision(const RandomObject& good, const RandomObject& bad); // checks collision beetwen texts
    bool IfTextClicked(RandomObject& obj); // check if text is clicked 
    void DrawEndScreen(bool isWin); // draw SUCCES or FAILURE 

public:
    FinderGame(float x, float y, float width, float height, const std::string& title);
    bool isFinderWin;
    void Update() override;
    void Draw() override;
};


#endif // FINDER_H