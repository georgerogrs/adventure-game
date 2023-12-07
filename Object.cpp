//
// Created by George Rogers on 07/12/2023.
//

#include "Object.h"

using namespace std;

Object::Object(string name, string description, Room* initialRoom) {
    this->name = name;
    this->description = description;
    this->initialRoom = initialRoom;
}

string Object::getName() {
    return name;
}

string Object::getDescription() {
    return description;
}

Room Object::getRoom() {
    return *initialRoom;
}

