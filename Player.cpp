//
// Created by George Rogers on 07/12/2023.
//

#include "Player.h"

using namespace std;

Player::Player(Room* initialRoom) {
    this->room = initialRoom;
    this->inventory = {};
}

Room Player::getRoom() {
    return *room;
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