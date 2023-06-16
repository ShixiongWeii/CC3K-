#ifndef __DRAGONHORDE_H__
#define __DRAGONHORDE_H__
#include "treasure.h"
class DragonHorde : public Treasure {
    bool isGuarded;
    bool ifBarrier;
public:
    DragonHorde(int, int, int, bool, bool);
    ~DragonHorde();
    bool getStatue();
    bool getBarrier();
    void setState(bool);
};

#endif
