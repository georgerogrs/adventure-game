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

    std::string move(std::string direction);

private:
    Room* room;
};


#endif //ADVENTURE_GAME_RETRY_PLAYER_H
