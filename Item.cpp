
#include "Item.h"
#include "GameBuilder.h"


Item::Item(string name, string description) : id(GameBuilder::getInstance().generateUnqiueId()), name(name), description(description) {}

string Item::getName() {return name;}

string Item::getDescription() {return description;}