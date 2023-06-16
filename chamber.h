#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <vector>
#include <iostream>
#include "character.h"
#include "basepotion.h"
#include "treasure.h"
#include "enemyFactory.h"
#include "playerFactory.h"
#include "dragonhorde.h"
#include "normal.h"
#include "small.h"
#include "defencepotion.h"
#include "attackpotion.h"
#include "healthpotion.h"

using namespace std;
 struct potionposn{
        int x;
        int y;
    };
    struct goldposn{
        int x;
        int y;
    };
    struct stairposn{
        int x;
        int y;
    };
class Chamber{
    int numChamber;
    int numEnemy;
    bool ifplayer;
    bool ifcompass;
    bool ifstair;
    int numPotion;
    int numGold;
    char race;
    bool ifsuite;
    player* curplayer;
    //potionposn pposn;
    vector<potionposn> Pposn;
    goldposn gposn;
    stairposn sposn;
    
    int numdragon;
    vector<enemy*> enemies;
    vector<Treasure*> goldPile;
    vector<Potion*> potions;
    public:
    bool getifplayer();
    bool getifcompass();
    bool getifstair();
    void createGold(int,int,char);
    vector<enemy*> getEnemies();
    vector<Treasure*> getTreasure();
    vector<Potion*> getPotions();
    player* getplayer();
    vector<potionposn> getpotionposn();
    goldposn getgoldposn();
    stairposn getstairposn();
    int getnumene();
    int getnumpotion();
    Chamber();
    Chamber(int,int,bool,bool,bool,int,int,char,bool);
    ~Chamber();
    int randomPos(int,int) const;
    void createPlayer(int,int,char);
    void createEnemy(int,int,char);
    void createPotion(int,int,string);
    char symbol(CharType character);
    void setplayer(player*);
    void setifsuite(bool);
    void eraseEnemy(int);
    void erasePotion(int);
    void eraseGold(int);
    void setstair(int, int);
};

#endif
