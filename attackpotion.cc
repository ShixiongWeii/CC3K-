#include "attackpotion.h"

AttackPotion::AttackPotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::AttackPotion;
    this->val = val;
}


void AttackPotion::enhance(player* player) {
    potion->enhance(player);
    int att = player->getAttack();
    int newAtt;
    if (player->getRace() == CharType::Elf) {
        newAtt = att + abs(this->val);
    } else {
        newAtt = att + (this->val); 
    }
    if (newAtt < 0) {
        newAtt = 0;
    }
    player->enhanceAttack(newAtt);
}

int AttackPotion::getX() {
    return potion->getX();
}

int AttackPotion::getY() {
    return potion->getY();
}


