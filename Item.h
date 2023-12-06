#ifndef ADVENTURE_GAME_ITEM_H
#define ADVENTURE_GAME_ITEM_H

#include <string>

using namespace std;

class Item {
public:
    Item(string name, string description);

    string getName();

    string getDescription();

private:
    int id;
    string name;
    string description;
};


#endif //ADVENTURE_GAME_ITEM_H
