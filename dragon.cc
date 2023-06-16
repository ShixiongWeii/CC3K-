#include "dragon.h"
#include <iostream>
using namespace std;

dragon::dragon(int x, int y, bool ifCompass, int horde_x, int horde_y): 
    enemy(CharType::Dragon, 150, 20, 20, 0, x, y, ifCompass), 
    horde_x{horde_x}, horde_y{horde_y} {}

void dragon::dragonmove() {
    int old_x = x;
    int old_y = y;
    while (true) {
        move();
        if (abs(x - horde_x) > 1 || abs(y - horde_y) > 1 || (x == horde_x && y == horde_y)) { 
            x = old_x;
            y = old_y;
        } else {
            break;
        }
    }
}

int dragon::getHorde_x() {
    return horde_x;
}

int dragon::getHorde_y() {
    return horde_y;
}
