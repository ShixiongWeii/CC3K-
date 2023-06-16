#ifndef __POTION_H__
#define __POTION_H__
#include "player.h"
#include <iostream>
enum class PotionType { NewPotion, HealthPotion, AttackPotion, DefencePotion };

class Potion {
protected:    
    int x;
    int y;
    int val;
    PotionType pt;
public:
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual void enhance(player*) = 0;
    virtual ~Potion() = default;
};



#endif

