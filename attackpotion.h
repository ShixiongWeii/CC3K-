#ifndef __ATTACKPOTION_H__
#define __ATTACKPOTION_H__
#include "decorator.h"
class AttackPotion : public Decorator {
public:
    AttackPotion(Potion*, int);
    void enhance(player*);
    int getX();
    int getY();
};

#endif

