#include "defencepotion.h"

DefencePotion::DefencePotion(Potion* potion, int val) : Decorator{potion} {
    this->pt = PotionType::DefencePotion;
    this->val = val;
}


void DefencePotion::enhance(player* player) { 
    potion->enhance(player);
    int def = (player)->getDefence();
    int newDef;
    if (player->getRace() == CharType::Elf) {
        newDef = def + abs(this->val);
    } else {
        newDef = def + (this->val); 
    }
    if (newDef < 0) {
        newDef = 0;
    } 
    player->enhanceDefence(newDef); 
}

int DefencePotion::getX() {
    return potion->getX();
}

int DefencePotion::getY() {
    return potion->getY();
}



