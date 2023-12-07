//
// Created by George Rogers on 07/12/2023.
//

#include "Room.h"

#include <utility>

using namespace std;

Room::Room(std::string name, std::string description, std::map<std::string, Room*> exits) {
    this->name = name;
    this->description = description;
    this->exits = exits;
}

string Room::getName() {
    return name;
}

string Room::getDescription() {
    return description;
}

map<string, Room*> Room::getExits() {
    return exits;
}

string Room::displayExits() {
    // No exits from the room
    if (exits.empty()) {
        return "There are no exits";
    }

    string response = "There is ";
    // Only one exit from the room
    if (exits.size() == 1) {
        response += "an exit to the ";
    } else {
        response += "exits to the ";
    }

    int count = 0;
    for (auto exit : exits) {
        count++;
        response += exit.first;

        // If second last exit, add "and"
        if (count == exits.size() - 1 && exits.size() > 1) {
            response += " and ";
        }
            // If not the last exit, add ", "
        else if (count != exits.size()) {
            response += ", ";
        }
    }
    return response;
}