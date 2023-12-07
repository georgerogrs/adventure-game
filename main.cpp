#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Room.h"
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

Room* buildMap(string level) {
    std::ifstream file(level);
    if (!file.is_open()) {
        std::cerr << "Error opening map file" << std::endl;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();

    json mapJson = json::parse(fileContent);
    map<string, Room*> roomMap;

    // First loop: Create all rooms without exits
    for (const auto& room : mapJson["rooms"]) {
        string roomId = room["id"];
        string roomDesc = room["desc"];
        roomMap[roomId] = new Room(roomId, roomDesc, map<string, Room*>());
    }

    // Second loop: Set exits for each room
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

    string initialRoomId = mapJson["player"]["initialroom"];
    Room* initialRoom = nullptr;

    if (roomMap.find(initialRoomId) != roomMap.end()) {
        initialRoom = roomMap[initialRoomId];
    } else {
        cerr << "Initial room not found in map data." << endl;
    }

    return initialRoom;
}


int main() {

    Room* initialRoom = buildMap("resources/map4.json");

    //Map Building
    map<string, Room*> exits1;
    Room room1("room1", "You fall into a dingy hole", exits1);

    map<string, Room*> exits2;
    exits2["north"] = &room1;
    Room room2("room2", "A vast open forest lies before you", exits2);

    Player player(initialRoom);

    bool endgame = true;


    cout << player.getRoom().getDescription() << endl;

    while (endgame) {
        string userInput;

        getline(cin, userInput);

        if (userInput == "show exits") {
            cout << player.getRoom().displayExits() << endl;
        }

        //Checks if user has typed "go"
        if (userInput.substr(0, 2) == "go") {
            string direction = userInput.substr(2);
            //Removes all whitespace
            trim(direction);
            cout << player.move(direction) << endl;
        }

        if (userInput == "quit game") {
            cout << "GAME OVER";
            endgame = false;
        }
    }
    return 0;
}
