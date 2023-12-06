#ifndef ADVENTURE_GAME_OBJECTIVE_H
#define ADVENTURE_GAME_OBJECTIVE_H

#include <string>
#include <vector>

using namespace std;

class Objective {
public:
    Objective(const string type, vector<string> what);
private:
    string type;
    vector<string> what;
};


#endif //ADVENTURE_GAME_OBJECTIVE_H
