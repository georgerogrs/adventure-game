//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_ENEMY_H
#define ADVENTURE_GAME_ENEMY_H

#include <string>

class Enemy {
public:
    Enemy(std::string name, std::string description, int aggression, std::vector<std::string> killedBy);

    std::string getName();
    std::string getDescription();
    int getAggression();
    std::vector<std::string> getKilledBy();
private:
    std::string name;
    std::string description;
    int aggression;
    std::vector<std::string> killedBy;
};


#endif //ADVENTURE_GAME_ENEMY_H
