#include <iostream>
#include "Room.h"
#include "Player.h"

using namespace std;

void trim(string &s) {
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p+1);
}


int main() {

    //Map Building
    map<string, Room*> exits1;
    Room room1("room1", "You fall into a dingy hole", exits1);

    map<string, Room*> exits2;
    exits2["north"] = &room1;
    Room room2("room2", "A vast open forest lies before you", exits2);

    Player player(&room2);

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
