#ifndef _CC3K_
#define _CC3K_
#include <iostream>
#include <vector>
#include "floor.h"
#include <fstream>

class cc3k {
    Floor* board;
public:
    cc3k();
    void initinput(char, ifstream&, int);
    void initdefault(char, int, int, int);
    void reset();
    void attack(int, int);
    void move(int, int);
    void print();
    bool ifnextfloor(int, int);
    bool ifPotion(int, int);
    int random();
    void refresh();
    bool ifAlive();
    void pprr(int);
    int getHealth();
    void userechp(int maxhp);
    void userecat(int maxat);
    void userecdf(int maxdf);
    void printscore();
    ~cc3k();
};

#endif
