#include "chamber.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
//output a random number
int Chamber::randomPos(int min,int max)const{
      vector<int> v;
      for(int i = min; i <= max; i++){
          v.emplace_back(i);
      }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( v.begin(), v.end(), rng );
    return v[0];
}

//create a player
void Chamber::createPlayer(int xpos, int ypos,char race){
    playerFactory PF;
    if(race == 'h'){
                curplayer = PF.createHuman(xpos,ypos);

    }else if (race == 'e'){
                curplayer = PF.createElf(xpos,ypos);
    }else if (race == 'd'){
                curplayer = PF.createDwarf(xpos,ypos);
    }else if(race == 'o'){
                curplayer = PF.createOrc(xpos,ypos);
    }
}
//create a gold
void Chamber::createGold(int xpos,int ypos,char rGold){
    enemyFactory EF;
    switch (rGold)
                {
                case 'n':goldPile.emplace_back( new Normal(xpos,ypos,1));
                    break;
                case 's':goldPile.emplace_back( new Small(xpos,ypos,2));
                    break;
                case 'd':
                numEnemy -= 1;
                if(ifsuite){
                    goldPile.emplace_back( new DragonHorde(xpos,ypos,0,true,true));
                    ifsuite = false;

                    if(xpos == 61){
                        if(ypos == 3 || ypos == 19){
                            enemies.emplace_back(EF.createDragon(xpos,ypos-1,false,xpos,ypos));
                        }else {
                            enemies.emplace_back(EF.createDragon(xpos,ypos+1,false,xpos,ypos));
                        }
                    }else if(xpos == 3 || xpos == 39 || xpos == 38 ||xpos == 37 || xpos == 65){
                        enemies.emplace_back(EF.createDragon(xpos+1,ypos,false,xpos,ypos));
                    }else {
                        enemies.emplace_back(EF.createDragon(xpos-1,ypos,false,xpos,ypos));
                    }
                }else {
                    goldPile.emplace_back(new DragonHorde(xpos,ypos,6,true,false));
                    if(xpos == 61){
                        if(ypos == 3 || ypos == 19){
                            enemies.emplace_back(EF.createDragon(xpos,ypos-1,false,xpos,ypos));
                        }else {
                            enemies.emplace_back(EF.createDragon(xpos,ypos+1,false,xpos,ypos));
                        }
                    }else if(xpos == 3 || xpos == 39 || xpos == 38 ||xpos == 37 || xpos == 65){
                        enemies.emplace_back(EF.createDragon(xpos+1,ypos,false,xpos,ypos));
                    }else {
                        enemies.emplace_back(EF.createDragon(xpos-1,ypos,false,xpos,ypos));
                    }
                }
                    break;
                }
                gposn.x = xpos;
                gposn.y = ypos;
}

//create an enemy
void Chamber::createEnemy(int xpos,int ypos, char enerace){
    enemyFactory EF;
    switch (enerace)
                {
                case 'w':enemies.emplace_back(EF.createWerewolf(xpos,ypos,false));
                    break;
                case 'v':enemies.emplace_back(EF.createVampire(xpos,ypos,false));
                    break;
                case 'g':enemies.emplace_back(EF.createGoblin(xpos,ypos,false));
                    break;
                case 't':enemies.emplace_back(EF.createTroll(xpos,ypos,false));
                    break;
                case 'p':enemies.emplace_back(EF.createPhoenix(xpos,ypos,false));
                    break;
                case 'm':enemies.emplace_back(EF.createMerchant(xpos,ypos,false));
                    break;
                }
}

//create a potion
void Chamber::createPotion(int xpos,int ypos, string prace){
    Potion* mypotion = new BasePotion(xpos,ypos);
    if(prace ==  "subDefence"){ 
        mypotion = new DefencePotion(mypotion, -5);
        potions.emplace_back(mypotion);
    }else if (prace == "addDefence"){
        mypotion = new DefencePotion(mypotion, 5);
        potions.emplace_back(mypotion);
    }else if (prace == "subAttack"){
        mypotion = new AttackPotion(mypotion, -5);
        potions.emplace_back(mypotion);
    }else if (prace == "addAttack"){
        mypotion = new AttackPotion(mypotion, 5);
        potions.emplace_back(mypotion);
    }else if ( prace == "subHealth"){
        mypotion = new HealthPotion(mypotion, -10);
        potions.emplace_back(mypotion);
    }else if (prace == "addHealth"){
        mypotion = new HealthPotion(mypotion, 10);
        potions.emplace_back(mypotion);
    }
    Pposn.emplace_back(potionposn{xpos,ypos});
}

player* Chamber::getplayer(){
    return curplayer;
}

vector<potionposn> Chamber::getpotionposn(){
    return Pposn;
}

goldposn Chamber::getgoldposn(){
    return gposn;
}

stairposn Chamber::getstairposn(){
    return sposn;
}

int Chamber::getnumene(){
    return numEnemy;
}

int Chamber::getnumpotion(){
    return numPotion;
}

Chamber::Chamber() {}

Chamber::Chamber(int numch,int numEne,bool player,bool compass,bool stair,int potion,int gold,char race,bool suite):
numChamber{numch},numEnemy{numEne},ifplayer{player},ifcompass{compass},ifstair{stair},numPotion{potion},numGold{gold},race{race},ifsuite{suite}{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    //make a player if nessecarry
    //factory
    //generate random enemies
    vector<char> ene = {'w','w','w','w','v','v','v','g','g','g','g','g','t','t','p','p','m','m'};
    vector<string> pot = {"subDefence","subDefence","addDefence","addDefence","subAttack","subAttack","addAttack","addAttack","subHealth","subHealth","addHealth","addHealth"};
    vector<char> gol = {'n','n','n','n','n','d','s','s'};
    char enelist[numEnemy];
    string poslist[numPotion];
    char goldlist[numGold];
    std::shuffle( ene.begin(), ene.end(), rng );
    for (int i  = 0; i < numEnemy; i++){
        enelist[i] = ene[i];
    }
    std::shuffle( pot.begin(), pot.end(), rng );
    for (int i  = 0; i < numPotion; i++){
        poslist[i] = pot[i];
    }
    std::shuffle( gol.begin(), gol.end(), rng );
    for (int i  = 0; i < numGold; i++){
        if(goldlist[i] == 'd'){
            numEnemy -= 1;
        }
        goldlist[i] = gol[i];
    }
    //make an occupied list
    struct occupyposn {
        int x;
        int y;
    };
    vector<occupyposn> vecposn;
    vector<vector<bool>> vacant;
    for(int h = 0; h < 25; h++){
        vacant.emplace_back(vector<bool>(79));
        for(int w = 0; w <79; w++){
            vacant[h][w]=true;
        }
    }
    int xpos;
    int ypos;
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////
    //if in the first chamber
    if(numChamber == 1){
        //create player
        if(ifplayer){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            createPlayer(xpos,ypos,race);
            vacant[ypos][xpos] = false;
            //cout<<"playerxpos"<<xpos<<"playerypos"<<ypos<<endl;
        }else {
            curplayer = nullptr;
        }
        //create stairways
        if(ifstair){
            
            while(true){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                sposn.x = xpos;
                sposn.y = ypos;
            
        }else {
            sposn.x = -1;
            sposn.y = -1;
        }
        //create potions
        for(int i = 0; i < numPotion;i++){
             while(true){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createPotion(xpos,ypos, poslist[i]);
            
        }
        //create gold
        for(int i = 0; i < numGold;i++){
              while(true){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
            //if valid position create enemy
            vacant[ypos][xpos] = false;
            createGold(xpos,ypos, goldlist[i]);
        }
        //create enemys
        for(int i = 0; i < numEnemy; i ++){
              while(true){
            xpos  = Chamber::randomPos(3,28);
            ypos = Chamber::randomPos(3,6);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createEnemy(xpos,ypos, enelist[i]);
            
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //if in the second chamber
    }else if(numChamber == 2){
        //create players
        if(ifplayer){
             ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,71);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            //cout<<"playerxpos"<<xpos<<"playerypos"<<ypos<<endl;
            createPlayer(xpos,ypos,race);
            vacant[ypos][xpos] = false;
        }else {
            curplayer = nullptr;
        }
        //create stairs
        if(ifstair){
            while(true){
            ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,71);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                sposn.x = xpos;
                sposn.y = ypos;
        }else {
            sposn.x = -1;
            sposn.y = -1;
        }
        //create potions
        for(int i = 0; i < numPotion;i++){
            while(true){
            ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,71);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createPotion(xpos,ypos, poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
              while(true){
            ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,71);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
            //if valid position create enemy
            vacant[ypos][xpos] = false;
            createGold(xpos,ypos, goldlist[i]);
        }

        //create enemies
        for(int i = 0; i < numEnemy; i ++){
             while(true){
           ypos = Chamber::randomPos(3,12);
            //different y position has different random x position
            if (ypos <= 4){
                xpos = Chamber::randomPos(39,61);
            }else if(ypos == 5){
                xpos = Chamber::randomPos(39,69);
            }else if (ypos == 6){
                xpos = Chamber::randomPos(39,72);
            }else {
                xpos = Chamber::randomPos(61,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createEnemy(xpos,ypos, enelist[i]);
        }
         ////////////////////////////////////////////////////////////////////
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
          //as above
    }else if(numChamber == 3){
        if(ifplayer){
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            createPlayer(xpos,ypos,race);
            vacant[ypos][xpos] = false;
            //cout<<"playerxpos"<<xpos<<"playerypos"<<ypos<<endl;
        }else{
            curplayer = nullptr;
        }
        if(ifstair){
            while(true){
           xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                sposn.x = xpos;
                sposn.y = ypos;
        }else {
            sposn.x = -1;
            sposn.y = -1;
        }
        for(int i = 0; i < numPotion;i++){
             while(true){
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createPotion(xpos,ypos, poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
               while(true){
             xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
            //if valid position create enemy
            vacant[ypos][xpos] = false;
            createGold(xpos,ypos, goldlist[i]);
        }
        for(int i = 0; i < numEnemy; i ++){
             while(true){
            //different y position has different random x position
            xpos  = Chamber::randomPos(38,49);
            ypos = Chamber::randomPos(10,12);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createEnemy(xpos,ypos, enelist[i]);
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //as above
    }else if(numChamber == 4){
        if(ifplayer){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            createPlayer(xpos,ypos,race);
            vacant[ypos][xpos] = false;
            //cout<<"playerxpos"<<xpos<<"playerypos"<<ypos<<endl;
        }else{
            curplayer = nullptr;
        }
        if(ifstair){
             while(true){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                sposn.x = xpos;
                sposn.y = ypos;
        }else {
            sposn.x = -1;
            sposn.y = -1;
        }
        for(int i = 0; i < numPotion;i++){
              while(true){
             xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createPotion(xpos,ypos, poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
              while(true){
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
            //if valid position create enemy
            vacant[ypos][xpos] = false;
            createGold(xpos,ypos, goldlist[i]);
        }
        for(int i = 0; i < numEnemy; i ++){
             while(true){
            //different y position has different random x position
            xpos  = Chamber::randomPos(4,24);
            ypos = Chamber::randomPos(15,21);
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createEnemy(xpos,ypos, enelist[i]);
        }
         ////////////////////////////////////////////////////////////////////
          ////////////////////////////////////////////////////////////////////
           ////////////////////////////////////////////////////////////////////
           //as above
    }else if(numChamber == 5){
        if(ifplayer){
             ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            createPlayer(xpos,ypos,race);
            vacant[ypos][xpos] = false;
            //cout<<"playerxpos"<<xpos<<"playerypos"<<ypos<<endl;
        }else {
            curplayer = nullptr;
        }
        if(ifstair){
             while(true){
            ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                sposn.x = xpos;
                sposn.y = ypos;
        }else {
            sposn.x = -1;
            sposn.y = -1;
        }
        for(int i = 0; i < numPotion;i++){
              while(true){
             ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createPotion(xpos,ypos, poslist[i]);
        }
        //create gold
        for(int i = 0; i < numGold;i++){
             while(true){
            ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
            //if valid position create enemy
            vacant[ypos][xpos] = false;
            createGold(xpos,ypos, goldlist[i]);
        }
        for(int i = 0; i < numEnemy; i ++){
            while(true){
            //different y position has different random x position
            ypos = Chamber::randomPos(16,21);
            //different y position has different random x position
            if (ypos <= 18){
                xpos = Chamber::randomPos(65,75);
            }else {
                xpos = Chamber::randomPos(37,75);
            }
            if(vacant[ypos][xpos] == true){
                break;
            }
            }
                vacant[ypos][xpos] = false;
                createEnemy(xpos,ypos, enelist[i]);
    }
    }
    //create compass
    if(ifcompass){
        std::shuffle( enemies.begin(), enemies.end(), rng );
        enemies[0]->setCompass(ifcompass);
        //std::cout << "Compass enemy " << enemies[0]->getX() << ' ' << enemies[0]->getY() << std::endl;
    }
}

bool Chamber::getifplayer(){
    return ifplayer;
}

bool Chamber::getifcompass(){
        return ifcompass;
}

bool Chamber::getifstair(){
        return ifstair;
}
vector<enemy*> Chamber::getEnemies(){
    return enemies;
}

vector<Treasure*> Chamber::getTreasure(){
    return goldPile;
}

vector<Potion*> Chamber::getPotions(){
    return potions;
}

/*
vector<gold*> Chamber::getGold(){
    return golds;
}
*/
Chamber :: ~Chamber(){
    
    for(size_t i = 0; i < enemies.size(); i ++){
        delete enemies[i];
    }
    enemies.clear();
    for(size_t i = 0; i < goldPile.size(); i ++){
        delete goldPile[i];
    }
    goldPile.clear();
    for(size_t i = 0; i < potions.size(); i ++){
        delete potions[i];
    }
    potions.clear();
   
}

char Chamber::symbol(CharType character) {
    if (character == CharType::Werewolf) {
        return 'W';
    }
    if (character == CharType::Vampire) {
        return 'V';
    }
    if (character == CharType::Goblin) {
        return 'N';
    }
    if (character == CharType::Merchant) {
        return 'M';
    }
    if (character == CharType::Phoenix) {
        return 'X';
    }
    if (character == CharType::Troll) {
        return 'T';
    }
    if (character == CharType::Dragon) {
        return 'D';
    }
    return 'a';
}

void Chamber::setifsuite(bool suite){
    ifsuite = suite;
}

void Chamber::setplayer(player* ptr) {
    curplayer = ptr;
}

void Chamber::eraseEnemy(int index) {
    enemies.erase(enemies.begin()+index);
}

void Chamber::erasePotion(int index) {
    potions.erase(potions.begin()+index);
}

void Chamber::eraseGold(int index) {
    goldPile.erase(goldPile.begin()+index);
}

void Chamber::setstair(int xpos,int ypos){
        sposn.x = xpos;
        sposn.y = ypos;
    }

