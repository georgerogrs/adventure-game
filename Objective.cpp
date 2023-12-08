//
// Created by George Rogers on 07/12/2023.
//

#include "Objective.h"

using namespace std;

Objective::Objective(string type, vector<string> tasks) {
    this->type = type;
    this->tasks = tasks;
}


string Objective::getType() {
    return type;
}

vector<string> Objective::getTasks() {
    return tasks;
}

void Objective::removeTask(string completedTask) {
    auto it = find(tasks.begin(), tasks.end(), completedTask);
    if (it != tasks.end()) {
        tasks.erase(it);
    } else {
        cerr << "Unable to remove task: Task not found" << endl;
    }
}

