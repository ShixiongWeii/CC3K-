#include "treasure.h"
Treasure::Treasure(int x, int y, int amount) : x{x}, y{y}, amount{amount} {}

int Treasure::getX() {
    return x;
}

int Treasure::getY() {
    return y;
}

int Treasure::getAmount() {
    return amount;
}

Treasure::~Treasure() {}

