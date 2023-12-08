#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <nlohmann/json.hpp>

#include "Room.h"
#include "Object.h"
#include "Player.h"
#include "Objective.h"


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

    //Create enemies
    map<int, Enemy*> allEnemies;
    int enemyCount = 0;
    //Create Enemies
    for (const auto& enemy : mapJson["enemies"]) {
        string enemyName = enemy["id"];
        string enemyDesc = enemy["desc"];
        int enemyAgg = enemy["aggressiveness"];

        vector<string> enemyKilledBy = enemy["killedby"];

        for (auto pair : roomMap) {
            if (pair.second->getName() == enemy["initialroom"]) {
                //Sets enemy to room
                pair.second->addEnemy(new Enemy(enemyName, enemyDesc, enemyAgg, enemyKilledBy));
            }
        }

        enemyCount++;
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

    //Create a win condition
    string objectiveType = mapJson["objective"]["type"];
    vector<string> taskList;
    for (const auto& task : mapJson["objective"]["what"]) {
        string taskToAdd = task;
        taskList.push_back(taskToAdd);
    }

    Objective objective(objectiveType, taskList);

    bool endgame = false;

    cout << player.getRoom().getDescription()<< endl;


    //Game starts
    while (!endgame) {

//        cout << objective.getType() << endl;
//        for (auto task: objective.getTasks()) {
//            cout << task << endl;
//        }

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

            //Have all enemies attack player
            int isAlive = true;
            for (auto enemy : player.getRoom().getEnemies()) {
                if (isAlive) {
                    bool survive = player.hurt(enemy->getAggression());
                    if (!survive) {
                        cout << enemy->getName() << " attacks and you die." << endl;
                        endgame = true;
                        isAlive = false;
                    }
                }
            }

            if (isAlive) {
                string direction = userInput.substr(2);
                //Removes all whitespace
                trim(direction);
                cout << player.move(direction) << endl;
            }
        }

        if (userInput.substr(0, 4) == "take") {
            string item = userInput.substr(4);
            //Removes all whitespace
            trim(item);
            cout << player.take(item) << endl;
        }

        if (userInput.substr(0, 4) == "kill") {
            string killWith = userInput.substr(4);
            trim(killWith);

            // Check contains the phrase "with"
            size_t withPosition = killWith.find(" with ");
            if (withPosition != string::npos) {
                string enemyName = killWith.substr(0, withPosition);
                string weaponName = killWith.substr(withPosition + 6);
                trim(enemyName);
                trim(weaponName);

                if (player.kill(enemyName, weaponName) == "ENDGAME") {
                    cout << "The weapon "+weaponName+" has no affect on "+enemyName+"." << endl;
                    cout << "The "+enemyName+" attacks you and you die."<< endl;
                    endgame = true;
                } else if (player.kill(enemyName, weaponName) == "ENEMYKILLED") {
                    //Finds matching enemy and removes it
                    for (auto enemy : player.getRoom().getEnemies()) {
                        if (enemy->getName() == enemyName) {
                            player.getRoom().removeEnemy(enemy);
                            cout << enemyName+" killed." << endl;

                            //Checks if task has been completed
                            if (objective.getType() == "kill") {
                                for (auto task : objective.getTasks()) {
                                    if (enemyName == task) {
                                        //Task completed
                                        objective.removeTask(task);
                                    }
                                }
                            }
                        }
                    }
                } else {
                    cout << player.kill(enemyName, weaponName) << endl;
                }
            }
        }

        if (userInput == "quit game") {
            endgame = true;
        }

        //Check if objectives.isEmpty() -> If so, win game!
        if (objective.getTasks().empty()) {
            cout << "You have won the game!" << endl;
            endgame = true;
        }
    }
    cout << "GAME OVER";
    return 0;
}
