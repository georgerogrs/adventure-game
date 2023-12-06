#ifndef ADVENTURE_GAME_PLAYER_H
#define ADVENTURE_GAME_PLAYER_H

#include <vector>

#include "Room.h"
#include "Item.h"

using namespace std;

class Player {
public:
    Player(Room initialRoom, vector<Item> initialInventory);

    string searchInventory();

private:
    int id;
    Room currentRoom;
    vector<Item> inventory;
};


#endif //ADVENTURE_GAME_PLAYER_H
