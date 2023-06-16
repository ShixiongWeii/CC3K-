#ifndef __SMALL_H__
#define __SMALL_H__
#include "treasure.h"
class Small : public Treasure {
public:
    Small(int x, int y, int amount);
    ~Small();
};
#endif
