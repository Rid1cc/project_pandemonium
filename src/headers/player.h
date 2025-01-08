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
};

class Player {
private:
    std::string name_;
    int level_;
    int experience_;

    std::string ipaddr_;
    int ports_[5];
    std::string mail_;
    std::string hostname_;

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

    void resetPlayer();

    std::string getIpAddr() const;
    void setIpAddr(std::string ipaddr);         
    int getPort(int index) const;
    void setPort(int index, int port);              
    std::string getMail() const;
    void setMail(std::string mail);                          
    void setHostname(std::string hostname);          
    std::string getHostname() const;


    std::string GetStatus() const;


};


#endif // PLAYER_H