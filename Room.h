//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_ROOM_H
#define ADVENTURE_GAME_RETRY_ROOM_H

#include <string>
#include <map>

#include "Object.h"

class Room {
public:
    Room();

    Room(std::string name, std::string description, std::map<std::string, Room*> exits);

    std::string getName();
    std::string getDescription();

    std::map<std::string, Room*> getExits();
    void addExit(std::pair<std::string, Room*> exit);

    std::vector<Object*>& getObjects();
    void addObject(Object* object);

    std::string displayExits();

private:
    std::string name;
    std::string description;

    std::map<std::string, Room*> exits;

    std::vector<Object*> objects;
};


#endif //ADVENTURE_GAME_RETRY_ROOM_H
