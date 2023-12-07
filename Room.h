//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_ROOM_H
#define ADVENTURE_GAME_RETRY_ROOM_H

#include <string>
#include <map>

class Room {
public:
    Room(std::string name, std::string description, std::map<std::string, Room*> exits);

    std::string getName();
    std::string getDescription();

    std::map<std::string, Room*> getExits();

    std::string displayExits();
private:
    std::string name;
    std::string description;

    std::map<std::string, Room*> exits;
};


#endif //ADVENTURE_GAME_RETRY_ROOM_H
