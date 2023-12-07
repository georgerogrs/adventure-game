//
// Created by George Rogers on 07/12/2023.
//

#include "Player.h"

using namespace std;

Player::Player(Room* initialRoom) {
    this->room = initialRoom;
}

Room Player::getRoom() {
    return *room;
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