//
// Created by George Rogers on 07/12/2023.
//

#include "Room.h"

#include <utility>

using namespace std;

Room::Room() {
    this->name = "";
    this->description = "";
    this->exits = map<string, Room*>();
    this->objects = {};
}

Room::Room(std::string name, std::string description, std::map<std::string, Room*> exits) {
    this->name = name;
    this->description = description;
    this->exits = exits;
    this->objects = {};
}

string Room::getName() {
    return name;
}

string Room::getDescription() {
    string response = description;

    if (objects.size() > 0) {
        response +=  " There is a ";

        int count = 0;
        for (auto object : objects) {
            count++;
            response += object->getName();

            // If second last exit, add "and"
            if (count == objects.size() - 1 && objects.size() > 1) {
                response += " and a ";
            }
                // If not the last exit, add ", "
            else if (count != objects.size()) {
                response += ", ";
            }
        }
    }

    return response;
}

map<string, Room*> Room::getExits() {
    return exits;
}

void Room::addExit(pair<string, Room*> exit) {
    exits.insert(exit);
}

std::vector<Object*>& Room::getObjects() {
    return this->objects; // Assuming `objects` is the member variable holding the objects
}

void Room::addObject(Object* object) {
    objects.push_back(object);
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