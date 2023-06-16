#ifndef _FLOOR_H_
#define _FLOOR_H_
#include <vector>
#include <iostream>
#include <fstream>
#include "chamber.h"
#include "passway.h"
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
class Floor{
    protected:
    bool usepotion = false;
    int Health;
    vector<vector<char>> map;
    vector<Chamber*> chambers;
    Passways* passways;
    bool ifAttackMerchant;
    bool ifBarrierSuite;
    bool ifCompassCarried;
    char whichrace;
    public:
    Floor(int, char,bool,ifstream&);
    Floor(int, char,bool);
    ~Floor();
    vector<int> randomPosn();
    bool ifdoor(int x, int y);
    int playerChamber();
    void attack(int x, int y);
    void move(int x, int y);
    void refresh();
    void print();
    bool ifnextfloor(int x, int y);
    bool ifPotion(int, int);
    void defaultArg(ifstream& );
    void setMap(int x, int y, char symbol);
    int doorChamber(int x, int y);
    bool ifAlive();
    bool dragonblock(int, int, int, int);
    bool ifNeighbour(int, int, int, int);
    void printMessage(int);
    int librarianHp = 0;
    int librarianAt = 0;
    int librarianDf = 0;
    vector<int> recordHp;
    vector<int> recordAt;
    vector<int> recordDf;
    void recordingHp(int);
    void recordingAt(int);
    void recordingDf(int);
    int getHealth();
    void printscore();
    
};


#endif

