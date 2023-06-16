#include "basepotion.h"

BasePotion::BasePotion(int x, int y) {
    this->x = x;
    this->y = y;
    this->val = 0;
    this->pt = PotionType::NewPotion;
}

int BasePotion::getX() {
    return x;
}

int BasePotion::getY() {
    return y;
}

int BasePotion::getVal() {
    return val;
}

PotionType BasePotion::getPt() {
    return pt;
}

void BasePotion::enhance(player* pl) {}

BasePotion::~BasePotion() {
}

