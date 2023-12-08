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
    this->enemies = {};
}

Room::Room(std::string name, std::string description, std::map<std::string, Room*> exits) {
    this->name = name;
    this->description = description;
    this->exits = exits;
    this->objects = {};
    this->enemies = {};
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

        response+=".";
    }

    if (enemies.size() > 0) {
        response +=  " There is a ";

        int count = 0;
        for (auto enemy : enemies) {
            count++;
            response += enemy->getName();

            // If second last exit, add "and"
            if (count == enemies.size() - 1 && enemies.size() > 1) {
                response += " and a ";
            }
                // If not the last exit, add ", "
            else if (count != enemies.size()) {
                response += ", ";
            }
        }
        response+=".";
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
    return this->objects;
}

void Room::addObject(Object* object) {
    objects.push_back(object);
}

std::vector<Enemy*>& Room::getEnemies() {
    return this->enemies;
}

void Room::addEnemy(Enemy *enemy) {
    enemies.push_back(enemy);
}

void Room::removeEnemy(Enemy *enemy) {
    auto newEnd = std::remove(enemies.begin(), enemies.end(), enemy);
    enemies.erase(newEnd, enemies.end());
}

string Room::displayExits() {
    // No exits from the room
    if (exits.empty()) {
        return "There are no exits";
    }

    string response = "Exits:\n";

    int count = 0;
    for (auto exit : exits) {
        count++;
        response += "- "+exit.first+"\n";
    }

    return response;
}