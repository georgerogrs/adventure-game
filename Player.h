//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_PLAYER_H
#define ADVENTURE_GAME_RETRY_PLAYER_H

#include "Room.h"

#include <iostream>

class Player {
public:
    Player(Room* initialRoom);

    Room& getRoom();

    std::vector<Object*> getInventory();

    int getLives();

    std::string displayInventory();

    std::string displayLives();

    std::string take(std::string object);

    std::string move(std::string direction);

    std::string kill(std::string who, std::string what);

    std:: string drop(std::string object, Room* room);

    void hurt(int attack);

    void loseLife();

private:
    Room* room;
    std::vector<Object*> inventory;
    int lives;
    int carryCapacity;
};


#endif //ADVENTURE_GAME_RETRY_PLAYER_H
