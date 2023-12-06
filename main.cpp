#include <iostream>
#include "Room.h"
#include "Item.h"
#include "Player.h"

int main() {

    //Room setup
    map<string, string> exits;
    exits["north"] = "You see a forest";
    exits["east"] = "There is a small lake";
    exits["west"] = "There is a huge window showing a vast mountain in the distance";

    //Items setup
    vector<Item> items;
    Item newItem("shovel", "A rusty shovel with a broken handle");
    items.push_back(newItem);
    Item newItem1("knife", "A sharp knife with a jagged edge");
    items.push_back(newItem1);


    Room newRoom("A small room with wooden walls", exits, items);

    //Player Setup
    vector<Item> inventory;
    Item newItem2("crowbar", "A crowbar - could be useful for prying open doors");
    inventory.push_back(newItem2);

    Player newPlayer(newRoom, inventory);



    cout << newRoom.getDescription() << endl;
    cout << newRoom.look() << endl;
    cout << newRoom.getExits() << endl;
    cout << newRoom.lookDirection("north") << endl;
    cout << newPlayer.searchInventory() << endl;

    return 0;
}
