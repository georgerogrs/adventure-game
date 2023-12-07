//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_PLAYER_H
#define ADVENTURE_GAME_RETRY_PLAYER_H

#include "Room.h"

class Player {
public:
    Player(Room* initialRoom);

    Room getRoom();

    std::string take(std::string object);

    std::string move(std::string direction);

    std::string displayInventory();
private:
    Room* room;
    std::vector<Object*> inventory;
};


#endif //ADVENTURE_GAME_RETRY_PLAYER_H
