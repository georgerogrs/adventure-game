#include "Player.h"
#include "GameBuilder.h"

Player::Player(Room initialRoom, vector<Item> initialInventory) : id(GameBuilder::getInstance().generateUnqiueId()), currentRoom(initialRoom), inventory(initialInventory){}

string Player::searchInventory() {
    if (inventory.empty()) {
        return "Your inventory is empty";
    } else {
        string response = "\nINVENTORY\n";
        for(int i=0;i<inventory.size();i++) {
            Item givenItem = inventory[i];
            response += "- "+givenItem.getName();
            if (i < inventory.size()-1) {
                response+="\n";
            }
        }

        return response;
    }
}

//TODO: function to move rooms