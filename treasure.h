#ifndef __TREASURE_H__
#define __TREASURE_H__

class Treasure {
protected:
    int x;
    int y;
    int amount;
public:
    Treasure(int x, int y, int amount);
    int getX();
    int getY();
    int getAmount();
    virtual ~Treasure();
};



#endif

