#ifndef _PASSWAY_H_
#define _PASSWAY_H_
#include <vector>
using namespace std;

class player;

class Passways {

    private:
    vector<vector <int> > posn;
    player* curplayer;
    public:
    vector<vector <int> > getposn();
    player* getplayer();
    void setplayer(player*);
    Passways();
    ~Passways();
};

#endif


