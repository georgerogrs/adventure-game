//
// Created by George Rogers on 07/12/2023.
//

#include "Enemy.h"

using namespace std;

Enemy::Enemy(std::string name, std::string description, int aggression, std::vector<std::string> killedBy) {
    this->name = name;
    this->description = description;
    this->aggression = aggression;
    this->killedBy = killedBy;
    this->isAlive = true;
}

string Enemy::getName() {
    return name;
}

string Enemy::getDescription() {
    return description;
}

int Enemy::getAggression() {
    return aggression;
}


vector<string> Enemy::getKilledBy() {
    return killedBy;
}

void Enemy::die() {
    isAlive = false;
}