#ifndef __HEALTHPOTION_H__
#define __HEALTHPOTION_H__
#include "decorator.h"
class HealthPotion : public Decorator {
public:
    HealthPotion(Potion*, int);
    void enhance(player*);
    int getX();
    int getY();
};

#endif

