//
// Created by George Rogers on 07/12/2023.
//

#ifndef ADVENTURE_GAME_RETRY_OBJECT_H
#define ADVENTURE_GAME_RETRY_OBJECT_H

#include <string>

class Object {
public:
    Object(std::string name, std::string description);

    std::string getName();
    std::string getDescription();
private:
    std::string name;
    std::string description;
};


#endif //ADVENTURE_GAME_RETRY_OBJECT_H
