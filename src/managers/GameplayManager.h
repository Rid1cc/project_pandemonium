#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H

#include "EventManager.h"

class GameplayManager {
public:
    GameplayManager();
    ~GameplayManager();

    void gameplayInit();
    void gameplayEnd();
    
    EventManager gameplayEvent;

private:
    int difficulty; // Variable to store difficulty level

    // Event handler functions
    void onStartCommand();
    void onStopCommand();
};

#endif

