#include "GameplayManager.h"
#include "../gameplay/gameplay_vars.h"
#include "../headers/globals.h"
#include <unordered_set>
#include <vector> // Added to use std::vector
#include <functional> // Added to use std::function
#include <algorithm> // Added to use std::shuffle
#include "../minigames/ConnectWiresGame.h"

// TimeManager implementation
// Its a simple class that counts down from a given number of seconds
TimeManager::TimeManager() : countdownFrames(0) {}

void TimeManager::setCountdown(float seconds) {
    countdownFrames = seconds * 60; // 60 frames per second
}

bool TimeManager::updateCountdown() {
    if (countdownFrames > 0) {
        countdownFrames--;
        //printf("Countdown: %d\n", countdownFrames);
        if (countdownFrames <= 0) {
            countdownFrames = 0;
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

void TimeManager::waitThen(float seconds, void (*func)()) {
    setCountdown(seconds);
    if(countdownFrames <= 0){
        func();
    }
}

// GameplayManager implementation
GameplayManager::GameplayManager() : 
    difficulty(1),
    rng2(std::random_device{}()),
    enemy("Enemy", 100), // Initialize enemy Player
    player("Steve", 100)
{
    
}

GameplayManager::~GameplayManager() {
    // Destructor implementation
}

void GameplayManager::gameplayInit() {
    // Enemy Initialization
    enemy.setHealth(100); // Set enemy health using setter

    // Open Port Randomizing with uniqueness check
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

    // IP Pool Randomizing with uniqueness check
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

    // Enemy IP
    std::uniform_int_distribution<int> enemyIPDist(0, 99);
    std::string generatedIP = ipPool[enemyIPDist(rng2)];
    enemy.setIpAddr(generatedIP); // Set enemy IP using setter
    if(debugMode != LOW)printf("Enemy IP: %s\n", generatedIP.c_str());

    // Set enemy Hostname using Player's setter
    const std::vector<std::string> demonNames = {
        "Asmodeus", "Belial", "Beelzebub", "Leviathan", "Mammon",
        "Astaroth", "Baal", "Lilith", "Samael", "Azazel",
        "Mephisto", "Paimon", "Abaddon", "Bifrons", "Dantalion",
        "Furfur", "Hai", "Ipos", "Jinn", "Marbas",
        "Orobas", "Phenex", "Stolas", "Vassago", "Zagan",
        "Andras", "Forneus", "Glasya", "Leraje", "Ronove"
    };
    std::uniform_int_distribution<int> nameDist(0, demonNames.size() - 1);
    std::string selectedName = demonNames[nameDist(rng2)];
    enemy.setHostname(selectedName); // Set hostname using setter
    if(debugMode != LOW)printf("Enemy Hostname: %s\n", selectedName.c_str());

    gameplayEvent.subscribe("startGame", [this]() { this->onStartCommand(); });
    gameplayEvent.subscribe("stopGame", [this]() { this->onStopCommand(); });
    gameplayEvent.subscribe("drainSilent", [this]() { this->onDrainSilent(); });
    gameplayEvent.subscribe("drainBruteforce", [this]() { this->onDrainBruteforce(); });
    gameplayEvent.subscribe("portscan", [this]() { this->onPortscan(); });
    gameplayEvent.subscribe("ddos", [this]() { this->onDdos(); });
    gameplayEvent.subscribe("startMiniGames", [this]() {this->onSafeMarginTimerEnd(); });

}

void GameplayManager::onSafeMarginTimerEnd() {
    printf("uruchomiono sekwencje minigier!\n");
    gameplayEvent.unsubscribe("startMiniGames", [this]() {this->onSafeMarginTimerEnd(); });
    printf("unsub dla \"startMiniGames\"\n");
    miniGamesManager.StartGameSequences(SelectedDifficulty);
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

void GameplayManager::onDrainBruteforce() {
    pidState = B_DRAIN;
    timer.setCountdown(30); //30 seconds
}

void GameplayManager::onDrainSilent() {
    pidState = S_DRAIN;
    timer.setCountdown(5);

    if(silentdraintimes == 0){
        // Initial drain: Select first 50 IPs
        old_selectedIpPool.assign(std::begin(ipPool), std::end(ipPool));
        int desiredSize = 50; // Initial desired pool size

        // Clear existing selectedIpPool and insert new elements
        selectedIpPool.clear();
        for(int i = 0; i < desiredSize && i < sizeof(ipPool)/sizeof(ipPool[0]); ++i){
            selectedIpPool.insert(ipPool[i]);
        }

        // Ensure enemyIp is included
        selectedIpPool.insert(enemyIp);
    }
    else {
        // Define the reduction sequence
        static const std::vector<int> drainStages = {50, 24, 14, 8, 4, 2, 1};
        int desiredSize = 1; // Default to 1 if all stages are completed

        // Determine the desired pool size for the current drain
        if(silentdraintimes < drainStages.size()){
            desiredSize = drainStages[silentdraintimes];
        }

        // Save current selectedIpPool to old_selectedIpPool
        old_selectedIpPool.assign(selectedIpPool.begin(), selectedIpPool.end());

        // Convert selectedIpPool to a vector for ordered access
        std::vector<std::string> tempSelected(selectedIpPool.begin(), selectedIpPool.end());

        // Shuffle the vector to randomize selection
        std::shuffle(tempSelected.begin(), tempSelected.end(), rng2);

        // Clear current selectedIpPool and insert the desired number of shuffled IPs
        selectedIpPool.clear();
        for(int i = 0; i < desiredSize && i < tempSelected.size(); ++i){
            selectedIpPool.insert(tempSelected[i]);
        }

        // Ensure enemyIp is included
        selectedIpPool.insert(enemyIp);

        // If only one address remains and countdown is not active, print it
        if(selectedIpPool.size() == 1 && !isCounting){
            printf("Final Address: %s\n", selectedIpPool.begin()->c_str()); // Fixed by adding .c_str()
            isEnemyIpKnown = true;
        }
    }
    // Increment silentdraintimes
    silentdraintimes++;
}

int GameplayManager::onPortscan() {
    pidState = PORTSCAN;
    timer.setCountdown(10); //10 seconds
    std::uniform_int_distribution<int> dist(0, 1);
    if(dist(rng2) == 1){
        std::uniform_int_distribution<int> rngport(0, 4);
        portscanResult = port[rngport(rng2)];
        std::cout << "Portscan: Open port found: " << portscanResult << std::endl;
        return portscanResult; // Replace 'portNumber' with the actual port retrieval logic
    } else {
        portscanResult = 0;
        return 0;
    }
}

void GameplayManager::onDdos() {
    pidState = DDOS;
    timer.setCountdown(50); //10 seconds
}



