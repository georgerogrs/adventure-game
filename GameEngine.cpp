#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

#include "Room.h"
#include "Object.h"
#include "Player.h"
#include "Objective.h"


using json = nlohmann::json;

namespace fs = std::filesystem;

using namespace std;

const string HINTLIST = " List of Commands:\n"
                        " - look/look around: Displays description of room\n"
                        " - look at (item/enemy): Displays description of item/enemy\n"
                        " - go (direction): Travels in that direction\n"
                        " - take (item): Takes item from room\n"
                        " - drop (item): Drops item in room\n"
                        " - list items: Displays items in inventory\n"
                        " - kill (enemy): Kills enemy (no item required)\n"
                        " - kill (enemy) with (item): Kills enemy with item\n"
                        " - show lives: Displays total hearts remaining\n"
                        " - hint exits: Shows all possible exits ** Removes 1 life **\n"
                        " - hint tasks: Shows all remaining tasks ** Removes 1 life **\n"
                        " - quit level: Takes you back to main menu";

const string LOTSOFSPACE = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

bool closeGame = false;

void trim(string &s) {
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}

string mainMenu() {

    string url = "resources/";

    cout << LOTSOFSPACE << "\n"
                           "\n"
                           "   ___     __              __                 ____               __ \n"
                           "  / _ |___/ /  _____ ___  / /___ _________   / __ \\__ _____ ___ / /_\n"
                           " / __ / _  / |/ / -_) _ \\/ __/ // / __/ -_) / /_/ / // / -_|_-</ __/\n"
                           "/_/ |_\\_,_/|___/\\__/_//_/\\__/\\_,_/_/  \\__/  \\___\\_\\_,_/\\__/___/\\__/ \n"
                           "===================================================================\n\n"
                           "";

    vector<string> levels;
    string path = "resources/"; // Path to the resources folder

    // Read all fileNames with extension JSON in resources folder
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".json") {
            levels.push_back(entry.path().filename().string());
        }
    }

    if (levels.size() <= 0) {
        cerr << "No levels available.\nTo load a level -> import a valid JSON file into the project resources folder.";
    } else if (levels.size() == 1) {
        url+=levels[0];
        cout << url;
        return url;
    } else {
        int count = levels.size();

        int userInput;

        cout << "                             Welcome!" << endl << endl;
        cout << "             Which level would you like to play? (1-" << count <<")\n\n\n" << endl << endl;
        cout << "                                                 Quit game? Type 99"<< endl;

        cin >> userInput;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (userInput == 99) {
            closeGame = true;
        } else if (userInput <= levels.size() && userInput > 0) {
            url+=levels[userInput];
            return url;
        } else {
            cout << "No such level. "<< endl;
            return mainMenu();
        }

        return "";
    }
}

int main() {

    while (true) {

        string url =  mainMenu();
        if (closeGame) {
            break;
        }

        //Display Loading Level timed for 3 seconds before loading level
        cout << LOTSOFSPACE <<"Loading Level." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << "." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout << LOTSOFSPACE << endl;

        std::ifstream file(url);
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

        bool win = false;
        //Game starts
        while (!endgame) {

            string userInput;

            getline(cin, userInput);

            if (userInput == "look" || userInput == "look around") {
                cout << player.getRoom().getDescription() << endl;
            }

            else if (userInput == "list items") {
                cout << player.displayInventory();
            }

            else if (userInput == "show lives") {
                cout << player.displayLives();
                cout << endl;
            }

            else if (userInput.substr(0, 7) == "look at") {
                string what = userInput.substr(7);

                trim(what);

                for (auto enemy : player.getRoom().getEnemies()) {
                    if (enemy->getName() == what) {
                        cout << enemy->getDescription() << endl;
                        break;
                    }
                }

                for (auto object : player.getRoom().getObjects()) {
                    if (object->getName() == what) {
                        cout << object->getDescription() << endl;
                        break;
                    }
                }

                for (auto object : player.getInventory()) {
                    if (object->getName() == what) {
                        cout << object->getDescription() << endl;
                        break;
                    }
                }
            }
                //Checks if user has typed "go"
            else if (userInput.substr(0, 2) == "go") {

                //Have all enemies attack player
                int isAlive = true;
                for (auto enemy : player.getRoom().getEnemies()) {
                    if (isAlive) {
                        int currentLives = player.getLives();
                        player.hurt(enemy->getAggression());
                        if (player.getLives() == 0) {
                            cout << "The " << enemy->getName() << " attacks and you die." << endl;
                            endgame = true;
                            isAlive = false;
                        } else if (player.getLives() < currentLives) {
                            cout << "The " << enemy->getName() << " attacks you." << endl;
                        }
                    }
                }

                if (isAlive) {
                    string direction = userInput.substr(2);
                    //Removes all whitespace
                    trim(direction);
                    cout << player.move(direction) << endl;

                    if (objective.getType() == "room") {
                        for (auto task : objective.getTasks()) {
                            if (task == player.getRoom().getName()) {
                                objective.removeTask(task);
                            }
                        }
                    }
                }
            }

            else if (userInput.substr(0, 4) == "take") {
                string item = userInput.substr(4);
                //Removes all whitespace
                trim(item);

                bool canTakeItem = true;

                if (!player.getRoom().getEnemies().empty()) {
                    player.loseLife();
                    if (player.getLives() == 0) {
                        cout << "The" << player.getRoom().getEnemies()[0]->getName() << " attacks you and you die." << endl;
                        endgame = true;
                        canTakeItem = false;
                    } else {
                        cout << "The " << player.getRoom().getEnemies()[0]->getName() << " attacks you." << endl;
                        canTakeItem = false;
                    }
                }

                if (canTakeItem) {
                    cout << player.take(item) << endl;

                    if (objective.getType() == "collect") {
                        for (auto task : objective.getTasks()) {
                            if (task == item) {
                                objective.removeTask(task);
                            }
                        }
                    }
                }
            }

            else if (userInput.substr(0, 4) == "drop") {
                string objectToDrop = userInput.substr(4);
                trim(objectToDrop);

                Room* playerRoomPtr = &player.getRoom();

                cout << player.drop(objectToDrop, playerRoomPtr) << endl;
            }

            else if (userInput.substr(0, 4) == "kill") {
                string killWith = userInput.substr(4);
                trim(killWith);

                // Initialize weaponName to "nothing" as a default
                string enemyName, weaponName = "nothing";

                // Check contains the phrase "with"
                size_t withPosition = killWith.find(" with ");
                if (withPosition != string::npos) {
                    enemyName = killWith.substr(0, withPosition);
                    weaponName = killWith.substr(withPosition + 6);
                } else {
                    enemyName = killWith; // No "with" found, whole string is enemyName
                }

                trim(enemyName);
                trim(weaponName);

                if (player.kill(enemyName, weaponName) == "ENDGAME") {
                    cout << "The weapon " << weaponName << " has no affect on " << enemyName << "." << endl;
                    player.loseLife();
                    if (player.getLives() <= 0) {
                        cout << "The " + enemyName + " attacks you and you die." << endl;
                        endgame = true;
                    } else {
                        cout << "The " + enemyName + " attacks you." << endl;
                    }
                } else if (player.kill(enemyName, weaponName) == "ENEMYKILLED") {
                    //Finds matching enemy and removes it
                    for (auto enemy : player.getRoom().getEnemies()) {
                        if (enemy->getName() == enemyName) {
                            player.getRoom().removeEnemy(enemy);
                            cout << "You kill the "+enemyName+"." << endl;

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

            else if (userInput == "quit level") {
                endgame = true;
            }

            else if (userInput == "hint exits") {
                cout << player.getRoom().displayExits();

                player.loseLife();
            }


            else if (userInput == "hint tasks") {
                cout << "Tasks (" << objective.getType() << ")" << endl;
                for (auto task : objective.getTasks()) {
                    cout << "- " << task << endl;
                }

                player.loseLife();
            }

            else if (userInput == "help") {
                cout << HINTLIST << endl;

            }

            else {
                cout << "Cannot understand (type 'help' for the list of commands). " << endl;
                cout << player.getRoom().getDescription() << endl;
            }

            if (player.getLives() <= 0) {
                cout << "You died";
                endgame = true;
            }
            //Check if objectives.isEmpty() -> If so, win game!
            if (objective.getTasks().empty()) {
                win = true;
                endgame = true;
            }
        }

        if (win) {
            cout << endl << "\n"
                            "\n"
                            "                                              (`\\ .-') /`            .-') _ ,---. \n"
                            "                                               `.( OO ),'           ( OO ) )|   | \n"
                            "  ,--.   ,--..-'),-----.  ,--. ,--.         ,--./  .--.  ,-.-') ,--./ ,--,' |   | \n"
                            "   \\  `.'  /( OO'  .-.  ' |  | |  |         |      |  |  |  |OO)|   \\ |  |\\ |   | \n"
                            " .-')     / /   |  | |  | |  | | .-')       |  |   |  |, |  |  \\|    \\|  | )|   | \n"
                            "(OO  \\   /  \\_) |  |\\|  | |  |_|( OO )      |  |.'.|  |_)|  |(_/|  .     |/ |  .' \n"
                            " |   /  /\\_   \\ |  | |  | |  | | `-' /      |         | ,|  |_.'|  |\\    |  `--'  \n"
                            " `-./  /.__)   `'  '-'  '('  '-'(_.-'       |   ,'.   |(_|  |   |  | \\   |  .--.  \n"
                            "   `--'          `-----'   `-----'          '--'   '--'  `--'   `--'  `--'  '--'  \n"
                            "";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            cout << endl << "\n"
                            "\n"
                            "           (`-')  _ <-. (`-')   (`-')  _                     (`-') (`-')  _   (`-')  \n"
                            "    .->    (OO ).-/    \\(OO )_  ( OO).-/         .->        _(OO ) ( OO).-/<-.(OO )  \n"
                            " ,---(`-') / ,---.  ,--./  ,-.)(,------.    (`-')----. ,--.(_/,-.\\(,------.,------,) \n"
                            "'  .-(OO ) | \\ /`.\\ |   `.'   | |  .---'    ( OO).-.  '\\   \\ / (_/ |  .---'|   /`. ' \n"
                            "|  | .-, \\ '-'|_.' ||  |'.'|  |(|  '--.     ( _) | |  | \\   /   / (|  '--. |  |_.' | \n"
                            "|  | '.(_/(|  .-.  ||  |   |  | |  .--'      \\|  |)|  |_ \\     /_) |  .--' |  .   .' \n"
                            "|  '-'  |  |  | |  ||  |   |  | |  `---.      '  '-'  '\\-'\\   /    |  `---.|  |\\  \\  \n"
                            " `-----'   `--' `--'`--'   `--' `------'       `-----'     `-'     `------'`--' '--' \n"
                            "";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }

    }

    return 0;
}