//
// Created by George Rogers on 07/12/2023.
//

#include <algorithm>
#include <string>
#include <vector>
#include <random>

#include "Player.h"

using namespace std;

const string GAMEOVER = "ENDGAME";
const string ENEMYKILLED = "ENEMYKILLED";

std::mt19937 rng(time(NULL));

Player::Player(Room* initialRoom) {
    this->room = initialRoom;
    this->inventory = {};
    this->lives = 3;
    this->carryCapacity = 3;
}

Room& Player::getRoom() {
    return *room;
}

vector<Object*> Player:: getInventory() {
    return inventory;
}

int Player::getLives() {
    return lives;
}

void Player::loseLife() {
    lives--;
}

string Player::displayInventory() {

    if (inventory.size() == 0) {
        return "You have no items in your inventory.";
    }

    string response = "Inventory:\n";
    for (auto it : inventory) {
        response += "- "+it->getName()+"\n";
    }

    return response;
}

string Player::displayLives() {
    string myLives = "";
    for (int i=0; i<lives;i++) {
        myLives+= "<3 ";
    }

    return myLives;
}

string Player::take(string object) {

    if (inventory.size() == carryCapacity) {
        return "Inventory at full capacity.";
    }

    // Access the room's objects directly to modify
    auto& objectsInRoom = room->getObjects();

    for (auto it = objectsInRoom.begin(); it != objectsInRoom.end(); ++it) {
        if (object == (*it)->getName()) {
            // Remove object from room
            inventory.push_back(*it);
            objectsInRoom.erase(it);
            return "You picked up the " +  object+".";
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
    if (what == "nothing") {
        isInInventory = true;
    }

    for (auto item : inventory) {
        if (what == item->getName()) {
            isInInventory = true;
            break;
        }
    }
    if (!isInInventory) {return "No object "+what+" in inventory.";}

    //Check if item kills enemy
    if (what == "nothing" && enemyToKill->getKilledBy().empty()) {
        return ENEMYKILLED;
    }

    for (auto weapon : enemyToKill->getKilledBy()) {
        if (weapon == what) {;
            return ENEMYKILLED;
        }
    }

    return GAMEOVER;
}

string Player::drop(std::string object, Room* room) {

    // Check if the item is in inventory
    bool itemInInv = false;
    Object* objectToDrop;
    auto it = inventory.begin();
    while (it != inventory.end()) {
        if (object == (*it)->getName()) {
            itemInInv = true;
            objectToDrop = *it;

            // Remove item from inventory
            it = inventory.erase(it);
            break;
        } else {
            ++it;
        }
    }

    if (!itemInInv) { return "No item " + object + " in inventory."; }

    // Drop item in room
    room->getObjects().push_back(objectToDrop);

    return "Item " + object + " dropped.";
}

void Player::hurt(int attack) {
    uniform_int_distribution<int> dist(1, 100);
    int chance = dist(rng);

//    cout << attack << " : " << chance << endl;

    if (chance < attack) {
        lives--;
    }
}
