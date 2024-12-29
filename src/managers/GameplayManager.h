#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H

#include "EventManager.h"
#include <random>

class GameplayManager {
public:
    GameplayManager();  //Constructor
    ~GameplayManager(); //Destructor

    void gameplayInit(); //Gameplay Initializer
    void gameplayEnd();  //Gameplay Uninitializer
    
    EventManager gameplayEvent;

private:
    int difficulty;             // Variable to store difficulty level
    int port[5];                // Variable to store open port numbers
    std::string ipPool[250];    // Variable to store IP pool
    std::string enemyIp;        // Variable to store enemy IP
    std::string botnetFlag[10]; // Variable to flag botnet computers
    int enemyHp;                // Variable to store enemy health points

    // Event handler functions
    void onStartCommand();
    void onStopCommand();
};

#endif

