//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_OBJECTIVE_H
#define ADVENTURE_GAME_OBJECTIVE_H

#include <iostream>
#include <string>

class Objective {
public:
    Objective(std::string type, std::vector<std::string> tasks);

    std::string getType();
    std::vector<std::string> getTasks();
    void removeTask(std::string completedTask);
private:
    std::string type;
    std::vector<std::string> tasks;
};


#endif //ADVENTURE_GAME_OBJECTIVE_H
