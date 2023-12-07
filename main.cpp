#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <nlohmann/json.hpp>

#include "Room.h"
#include "Object.h"
#include "Player.h"


using json = nlohmann::json;

using namespace std;

void trim(string &s) {
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}

int main() {

    std::ifstream file("resources/map1.json");
    if (!file.is_open()) {
        std::cerr << "Error opening map file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();

    json mapJson = json::parse(fileContent);
    map<string, Room*> roomMap;

    // Create all rooms without exits initially
    for (const auto& room : mapJson["rooms"]) {
        string roomId = room["id"];
        string roomDesc = room["desc"];
        roomMap[roomId] = new Room(roomId, roomDesc, map<string, Room*>());
    }

    // Set exits for each room
    for (const auto& room : mapJson["rooms"]) {
        string roomId = room["id"];
        auto& currentRoom = roomMap[roomId];

        for (const auto& exit : room["exits"].items()) {
            string exitDirection = exit.key();
            string exitToRoomId = exit.value();

            if (roomMap.find(exitToRoomId) != roomMap.end()) {
                currentRoom->addExit(make_pair(exitDirection, roomMap[exitToRoomId]));
            }
        }
    }

    map<int, Object*> allObjects;
    int objectCount = 0;

    //Create Objects
    for (const auto& object : mapJson["objects"]) {
        string objectName = object["id"];
        string objectDesc = object["desc"];

        for (auto pair : roomMap) {
            if (pair.second->getName() == object["initialroom"]) {

                //Sets object to room
                pair.second->addObject(new Object(objectName, objectDesc));
            }
        }

        objectCount++;
    }

    //Create Player's starting point
    string initialRoomId = mapJson["player"]["initialroom"];
    Room* initialRoom = nullptr;

    if (roomMap.find(initialRoomId) != roomMap.end()) {
        initialRoom = roomMap[initialRoomId];
    } else {
        cerr << "Initial room not found in map data." << endl;
    }


    Player player(initialRoom);

    bool endgame = true;


    cout << player.getRoom().getDescription()<< endl;


    //Game starts
    while (endgame) {
        string userInput;

        getline(cin, userInput);

        if (userInput == "look") {
            cout << player.getRoom().getDescription() << endl;
        }

        if (userInput == "show exits") {
            cout << player.getRoom().displayExits() << endl;
        }

        if (userInput == "list items") {
            cout << player.displayInventory() << endl;
        }

        //Checks if user has typed "go"
        if (userInput.substr(0, 2) == "go") {
            string direction = userInput.substr(2);
            //Removes all whitespace
            trim(direction);
            cout << player.move(direction) << endl;
        }

        if (userInput.substr(0, 4) == "take") {
            string item = userInput.substr(4);
            //Removes all whitespace
            trim(item);
            cout << player.take(item) << endl;

            for (auto it : player.getRoom().getObjects()) {
                cout << it->getName() << endl;
            }
        }

        if (userInput == "quit game") {
            cout << "GAME OVER";
            endgame = false;
        }
    }
    return 0;
}
