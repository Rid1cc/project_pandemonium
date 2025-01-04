#ifndef GAMEPLAYMANAGER_H
#define GAMEPLAYMANAGER_H

#include "EventManager.h"
#include <random>
#include <string> // Added to include std::string
#include <unordered_set> // Added to include std::unordered_set

// Forward declaration of TimeManager
class TimeManager {
public:
    TimeManager();
    void setCountdown(float seconds);
    bool updateCountdown();
    bool isCounting();
    int countdownFrames;
    void waitThen(float seconds, void (*func)());
private:

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
    std::unordered_set<std::string> selectedIpPool; // Updated from previous type
    std::vector<std::string> old_selectedIpPool;
    int portscanResult;         // Variable to store portscan result

private:
    // Add TimeManager instance
    int silentdraintimes = 0;
    
    std::mt19937 rng2;          // Random number generator

    // Add persistent distributions
    std::uniform_int_distribution<int> distPortscan; // Added for portscan distribution
    std::uniform_int_distribution<int> distRngPort;  // Added for port selection distribution

    // Event handler functions
    void onStartCommand();
    void onStopCommand();
    void onDrainSilent();
    void onDrainBruteforce();
    int onPortscan();
};

#endif

