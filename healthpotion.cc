#include "healthpotion.h"

HealthPotion::HealthPotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::HealthPotion;
    this->val = val;
}


void HealthPotion::enhance(player* player) {
    potion->enhance(player);
    int hlt = player->getHealth();
    int newhlt;
    if (player->getRace() == CharType::Elf) {
        newhlt = hlt + abs(this->val);
    } else {
        newhlt = hlt + (this->val);
    }
    if (newhlt < 0) {
        newhlt = 0;
    } 
    if (player->getRace() == CharType::Human) {
        if (newhlt > 140) {
            newhlt = 140;
        }
    } else if (player->getRace() == CharType::Dwarf) {
        if (newhlt > 100) {
            newhlt = 100;
        }
    } else if (player->getRace() == CharType::Elf) {
        if (newhlt > 140) {
            newhlt = 140;
        }
    } else {
        if (newhlt > 180) {
            newhlt = 180;
        }
    }
    player->enhanceHealth(newhlt);
}

int HealthPotion::getX() {
    return potion->getX();
}

int HealthPotion::getY() {
    return potion->getY();
}



