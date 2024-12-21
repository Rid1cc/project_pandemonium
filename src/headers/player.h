#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_set>

enum class Status {
    None,
    Attacking,
    Defending,
    SearchingForOpponent,
    FoundOpponent,
    DoingDDOS,
    DoingMailBomb,
    DoingBotnet

    // other status??
};

class Player {
private:
    std::string name_;
    int level_;
    int experience_;
    
    int health_;
    int maxHealth_;

    Status status_;

public:
    Player(const std::string& name, int maxHealth, int level = 1);     // Constructor
    ~Player() = default;    // Destructor

    // Health Management
    int getHealth() const;
    int getMaxHealth() const;
    void takeDamage(int amount);
    void heal(int amount);
    void setHealth(int health);

    // Status Management
    Status getStatus() const;
    void setStatus(Status status);
    bool hasStatus(Status status) const;

    // Attribute accessors
    std::string getName() const;
    int getLevel() const;
    void levelUp();
    void addExperience(int amount);
    int getExperience() const;

    std::string GetStatus() const;


};


#endif // PLAYER_H