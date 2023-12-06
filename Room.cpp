#include "Room.h"
#include "GameBuilder.h"

Room::Room(std::string description, map<std::string, std::string> exits, vector<Item> items) : id(GameBuilder::getInstance().generateUnqiueId()), description(description), exits(exits), items(items){}

string Room::getDescription() {
    return description;
}

string Room::look() {
    if (items.empty()) {
        return "You find nothing";
    } else {
        string response = "You find a ";
        for (int i = 0; i < items.size(); i++) {
            Item givenItem = items[i];
            response += givenItem.getName();
            if (i < items.size() - 2) {
                response += ", a "; // For items before the penultimate one, add ", a "
            } else if (i == items.size() - 2) {
                response += " and a "; // For the penultimate item, add " and a "
            }
            // The last item will just end without an additional conjunction or comma
        }

        return response;
    }
}


