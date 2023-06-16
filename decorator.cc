#include "decorator.h"

Decorator::Decorator(Potion* p) : 
    potion{p} {}

Decorator::~Decorator() {
    delete potion;
}


void Decorator::enhance(player* pl) {}

int Decorator::getX() {
    return x;
}

int Decorator::getY() {
    return y;
}


