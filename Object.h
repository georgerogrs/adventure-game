//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_OBJECT_H
#define ADVENTURE_GAME_RETRY_OBJECT_H

#include <string>
#include "Room.h"

class Object {
public:
    Object(std::string name, std::string description, Room* initialRoom);

    std::string getName();
    std::string getDescription();

    Room getRoom();
private:
    std::string name;
    std::string description;

    Room* initialRoom;
};


#endif //ADVENTURE_GAME_RETRY_OBJECT_H
