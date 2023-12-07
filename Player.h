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

    std::string displayInventory();

    std::string take(std::string object);

    std::string move(std::string direction);

    std::string kill(std::string who, std::string what);
private:
    Room* room;
    std::vector<Object*> inventory;
};


#endif //ADVENTURE_GAME_RETRY_PLAYER_H
