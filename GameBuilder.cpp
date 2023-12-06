#include "GameBuilder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

// Initialize the static set for unique ID tracking
unordered_set<int> GameBuilder::ids;

GameBuilder::GameBuilder() {
    // Initialize the random seed
    srand(static_cast<unsigned int>(time(nullptr)));
}

int GameBuilder::generateUnqiueId() {
    int uniqueId;
    do {
        // Generate a random ID between 1 and 1000
        uniqueId = rand() % 1000 + 1;
    } while (ids.find(uniqueId) != ids.end()); // Check if the ID is already used

    ids.insert(uniqueId); // Mark this ID as used
    return uniqueId;
}
