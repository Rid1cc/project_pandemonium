#include "GameplayManager.h"
#include "../headers/globals.h"
#include <unordered_set>
#include <vector> // Added to use std::vector

// TimeManager implementation
// Its a simple class that counts down from a given number of seconds
TimeManager::TimeManager() : countdownFrames(0) {}

void TimeManager::setCountdown(int seconds) {
    countdownFrames = seconds * 60; // 60 frames per second
}

bool TimeManager::updateCountdown() {
    if (countdownFrames > 0) {
        countdownFrames--;
        printf("Countdown: %d\n", countdownFrames);
        if (countdownFrames <= 0) {
            return false;
        }
    }
    return true;
}

bool TimeManager::isCounting() {
    if (countdownFrames > 0) {
        return true;
    } else {
        return false;
    }
}

// GameplayManager implementation
GameplayManager::GameplayManager() : 
    difficulty(1),
    rng2(std::random_device{}())
{
    
}

GameplayManager::~GameplayManager() {
    // Destructor implementation
}

void GameplayManager::gameplayInit() {
    //Enemy HP
    enemyHp = 100;

    //Open Port Randomizing with uniqueness check
    std::unordered_set<int> usedPorts;
    for(int i = 0; i < (sizeof(port)/sizeof(port[0])); i++) {
        int newPort;
        do {
            std::uniform_int_distribution<int> ports(1, 65535);
            newPort = ports(rng2);
        } while(usedPorts.find(newPort) != usedPorts.end());
        usedPorts.insert(newPort);
        port[i] = newPort;
        if(debugMode != LOW)printf("Port %d: %d\n", i, port[i]);
    }

    //IP Pool Randomizing with uniqueness check
    std::unordered_set<std::string> usedIPs;
    for(int i = 0; i < (sizeof(ipPool)/sizeof(ipPool[0])); i++) {
        std::string newIP;
        do {
            std::uniform_int_distribution<int> ipDist(0, 255);
            newIP = std::to_string(ipDist(rng2)) + "." + 
                    std::to_string(ipDist(rng2)) + "." + 
                    std::to_string(ipDist(rng2)) + "." + 
                    std::to_string(ipDist(rng2));
        } while(usedIPs.find(newIP) != usedIPs.end());
        usedIPs.insert(newIP);
        ipPool[i] = newIP;
        if(debugMode != LOW)printf("IP %d: %s\n", i, ipPool[i].c_str());
    }

    //Enemy IP
    std::uniform_int_distribution<int> enemyIPDist(0, 99);
    enemyIp = ipPool[enemyIPDist(rng2)];
    if(debugMode != LOW)printf("Enemy IP: %s\n", enemyIp.c_str());

    // Add randomizer for enemyHostname with biblical demon names
    const std::vector<std::string> demonNames = {
        "Asmodeus", "Belial", "Beelzebub", "Leviathan", "Mammon",
        "Astaroth", "Baal", "Lilith", "Samael", "Azazel",
        "Mephisto", "Paimon", "Abaddon", "Bifrons", "Dantalion",
        "Furfur", "Hai", "Ipos", "Jinn", "Marbas",
        "Orobas", "Phenex", "Stolas", "Vassago", "Zagan",
        "Andras", "Forneus", "Glasya", "Leraje", "Ronove"
    };
    std::uniform_int_distribution<int> nameDist(0, demonNames.size() - 1);
    enemyHostname = demonNames[nameDist(rng2)];
    if(debugMode != LOW)printf("Enemy Hostname: %s\n", enemyHostname.c_str());
    
    gameplayEvent.subscribe("startGame", [this]() { this->onStartCommand(); });
    gameplayEvent.subscribe("stopGame", [this]() { this->onStopCommand(); });
    gameplayEvent.subscribe("drain", [this]() { this->onDrainCommand(); });

}

void GameplayManager::gameplayEnd() {
    // Cleanup code

    // Unsubscribe from events if necessary
    gameplayEvent.unsubscribe("startGame", [this]() { this->onStartCommand(); });
    gameplayEvent.unsubscribe("stopGame", [this]() { this->onStopCommand(); });
}
// Event handler for "startGame" command
void GameplayManager::onStartCommand() {
    // Handle start game event
    if(debugMode != LOW)std::cout << "Game Started with difficulty level: " << difficulty << std::endl;
    timer.setCountdown(30); // Set countdown to 30 seconds
    printf("Countdown initialized to 30 seconds.\n");
}

// Event handler for "stopGame" command
void GameplayManager::onStopCommand() {
    // Handle stop game event
    if(debugMode != LOW)std::cout << "Game Stopped." << std::endl;
    timer.setCountdown(0); // Stop countdown
    // Additional stop game logic
}

void GameplayManager::onDrainCommand() {
    // Handle drain command
    if(debugMode != LOW)std::cout << "Draining enemy resources..." << std::endl;
    enemyHp -= 10; // Drain enemy resources
    if(debugMode != LOW)std::cout << "Enemy HP: " << enemyHp << std::endl;
    // Additional drain logic
}

