#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H

#include "EventManager.h"
#include <random>
#include <string> // Added to include std::string

// Forward declaration of TimeManager
class TimeManager {
public:
    TimeManager();
    void setCountdown(int seconds);
    bool updateCountdown();
    bool isCounting();
private:
    int countdownFrames;
};

class GameplayManager {
public:
    GameplayManager();  // Constructor
    ~GameplayManager(); // Destructor

    void gameplayInit(); // Gameplay Initializer
    void gameplayEnd();  // Gameplay Uninitializer
    
    EventManager gameplayEvent; // EventManager instance
    TimeManager timer;          // TimeManager instance
    int difficulty;             // Variable to store difficulty level
    int port[5];                // Variable to store open port numbers
    std::string ipPool[100];    // Variable to store IP pool
    std::string enemyIp;        // Variable to store enemy IP
    std::string botnetFlag[10]; // Variable to flag botnet computers
    int enemyHp;                // Variable to store enemy health points
    std::string enemyHostname;  // Changed from int to std::string
    int enemyMail;              // Variable to store enemy mail

private:
    // Add TimeManager instance
    
    std::mt19937 rng2;          // Random number generator
    // Event handler functions
    void onStartCommand();
    void onStopCommand();
    void onDrainCommand();
};

#endif

