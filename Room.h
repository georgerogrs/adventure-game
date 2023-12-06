#ifndef ADVENTURE_GAME_ROOM_H
#define ADVENTURE_GAME_ROOM_H

#include <vector>
#include <string>
#include <map>

#include "Item.h"

using namespace std;

class Room {
public:
    Room(string description, map<string, string> exits, vector<Item> items);

    string getDescription();

    string getExits();

    string look();

    string lookDirection(string direction);
private:
    int id;
    string description;
    map<string, string> exits;
    vector<Item> items;
};


#endif //ADVENTURE_GAME_ROOM_H
