#include "dragonhorde.h"

DragonHorde::DragonHorde(int x, int y, int amount, bool ig, bool ib) : 
    Treasure{x, y, amount}, isGuarded{ig}, ifBarrier{ib} {}

DragonHorde::~DragonHorde() {}

bool DragonHorde::getStatue() {
    return isGuarded;
}

bool DragonHorde::getBarrier() {
    return ifBarrier;
}

void DragonHorde::setState(bool new_state) {
    isGuarded = new_state;
}

