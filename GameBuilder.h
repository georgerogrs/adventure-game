#ifndef ADVENTURE_GAME_GAMEBUILDER_H
#define ADVENTURE_GAME_GAMEBUILDER_H

#include <unordered_set>

using namespace std;

class GameBuilder {
public:
    static GameBuilder& getInstance() {
        static GameBuilder instance;
        return instance;
    }

    int generateUnqiueId();

    // Delete copy constructor and assignment operator
    GameBuilder(GameBuilder const&) = delete;
    void operator=(GameBuilder const&) = delete;

private:
    GameBuilder();
    static unordered_set<int> ids;
};



#endif //ADVENTURE_GAME_GAMEBUILDER_H
