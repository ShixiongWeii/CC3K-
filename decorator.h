#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include "potion.h"
#include <cstdlib>

class Decorator : public Potion {
protected:
    Potion* potion;
public:
    Decorator(Potion*);
    virtual int getX();
    virtual int getY();
    virtual void enhance(player*);
    ~Decorator() = 0;
};
#endif
