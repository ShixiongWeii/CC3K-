#ifndef __BASEPOTION_H__
#define __BASEPOTION_H__
#include "potion.h"
#include <iostream>
class BasePotion : public Potion{
public:
    BasePotion(int x, int y);
    int getX();
    int getY();
    int getVal();
    PotionType getPt();
    void enhance(player*);
    ~BasePotion();
};
#endif



