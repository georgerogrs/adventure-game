#ifndef ADVENTURE_GAME_ENEMY_H
#define ADVENTURE_GAME_ENEMY_H

#include <string>
#include "Room.h"
#include "Item.h"

using namespace std;

class Enemy {
public:
    Enemy(string name, string description, int aggression, Room initialRoom, Item killedBy);

private:
    int id;
    string name;
    string description;
    int aggression;
    Room currentRoom;
    Item killedBy;
};

#endif // ADVENTURE_GAME_ENEMY_H