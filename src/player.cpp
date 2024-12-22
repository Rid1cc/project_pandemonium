#include "headers/player.h"
#include <algorithm>
#include <iostream>

// Constructor
Player::Player(const std::string& name, int maxHealth, int level)
    : name_(name), level_(level), experience_(0), health_(maxHealth), maxHealth_(maxHealth) {}


// Health
int Player::getHealth() const {
    return health_;
}

int Player::getMaxHealth() const {
    return maxHealth_;
}

void Player::takeDamage(int amount) {
    if (health_ - amount >= 0) 
        health_ -= amount;
    else 
        health_ = 0;
}

void Player::heal(int amount) {
    if (health_ + amount <= maxHealth_)
        health_ += amount;
    else 
        health_ = maxHealth_;
}

void Player::setHealth(int health) {
    if (health > 0 && health < maxHealth_) 
        health_ = health;
}

// Status
Status Player::getStatus() const {
    return status_;
}

void Player::setStatus(Status status) {
    status_ = status;
}

bool Player::hasStatus(Status status) const{
    if (status_ == status)
        return true;
}

// Atrubutes
std::string Player::getName() const {
    return name_;
}

int Player::getLevel() const {
    return level_;
}

void Player::levelUp() {
    level_++;
}

void Player::addExperience(int amount) {
    experience_ += amount;
}

int Player::getExperience() const {
    return experience_;
}
