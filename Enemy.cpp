#include "Enemy.h"
#include "GameBuilder.h"

Enemy::Enemy(string name, string description, int aggression, Room initialRoom, Item killedBy)
        : id(GameBuilder::getInstance().generateUnqiueId()), name(name), description(description), aggression(aggression), currentRoom(initialRoom), killedBy(killedBy) {
}

string Enemy::getName() {
    return name;
}

string Enemy::getDescription() {
    return description;
}

//TODO: die function