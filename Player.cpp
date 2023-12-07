//
// Created by George Rogers on 07/12/2023.
//

#include <algorithm>
#include <string>
#include <vector>

#include "Player.h"

using namespace std;

const string GAMEOVER = "ENDGAME";

const string ENEMYKILLED = "WIN";

Player::Player(Room* initialRoom) {
    this->room = initialRoom;
    this->inventory = {};
}

Room& Player::getRoom() {
    return *room;
}

string Player::displayInventory() {

    if (inventory.size() == 0) {
        return "You have no items in your inventory.";
    }

    string response = "INVENTORY:\n";
    for (auto it : inventory) {
        response += "- "+it->getName()+"\n";
    }

    return response;
}

string Player::take(string object) {
    // Access the room's objects directly to modify
    auto& objectsInRoom = room->getObjects();

    for (auto it = objectsInRoom.begin(); it != objectsInRoom.end(); ++it) {
        if (object == (*it)->getName()) {
            // Remove object from room
            inventory.push_back(*it);
            objectsInRoom.erase(it);
            return "You picked up a" +  object;
        }
    }

    return "You cannot find a " + object;
}


string Player::move(string direction) {
    for (auto exit : room->getExits()) {
        if (exit.first == direction) {
            room = exit.second;
            return room->getDescription();
        }
    }

    return "Unable to move in direction "+direction;
}

string Player::kill(std::string who, std::string what) {

    //Check if enemy in room
    bool isInRoom = false;
    Enemy* enemyToKill;
    for (auto enemy : this->room->getEnemies()) {
        if (who == enemy->getName()) {
            enemyToKill = enemy;
            isInRoom = true;
            break;
        }
    }
    if (!isInRoom) {return "No enemy "+who+" in room.";}

    //Check if item in inventory
    bool isInInventory = false;
    for (auto item : inventory) {
        if (what == item->getName()) {
            isInInventory = true;
            break;
        }
    }
    if (!isInInventory) {return "No object "+what+" in inventory.";}

    //Check if item kills enemy
    for (auto weapon : enemyToKill->getKilledBy()) {
        if (weapon == what) {;
            return ENEMYKILLED;
        }
    }

    return GAMEOVER;
}
