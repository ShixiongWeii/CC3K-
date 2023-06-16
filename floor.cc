#include "floor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
Floor::Floor(int health, char race,bool suite){
    //used to randomly generate chamber
    ifBarrierSuite = suite;
    whichrace = race;
    Health = health;
    vector<int> v = {0,1,2,3,4};
    vector<bool> vplayer ={true, false, false, false, false};
    vector<bool> vcompass ={true, false, false, false, false};
    vector<bool> vstair ={true, false, false, false, false};
    vector<bool> vsuite ={true, false, false, false, false};
    if(suite == false){
        vsuite[0] = false;
    }
    //number of enemies in each chamber
    int numEne[5] = {0,0,0,0,0};
    int numPotion[5]= {0,0,0,0,0};
    int numGold[5] = {0,0,0,0,0,};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( vplayer.begin(), vplayer.end(), rng );
    std::shuffle( vcompass.begin(), vcompass.end(), rng );
    std::shuffle( vstair.begin(), vstair.end(), rng );
    std::shuffle( vsuite.begin(), vsuite.end(), rng );
    for ( int i = 0; i < 10; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numPotion[addNum] += 1;
	} 
    for ( int i = 0; i < 10; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numGold[addNum] += 1;
	} 
    for ( int i = 0; i < 20; i++ ) {
		//std::shuffle( v.begin(), v.end(), std::default_random_engine(seed) );
		std::shuffle( v.begin(), v.end(), rng );
		int addNum = v[0];
        //enemies + 1
        numEne[addNum] += 1;
	} 
    ifstream in ("map.txt");
    int compassChamber;
    for (int i = 0; i < 500; i++) {
        for (int i = 0; i < 5; i++) {
        if (vcompass[i] == 1) {
            compassChamber = i;
            }
        }
        if (numEne[compassChamber] == 0) {
            std::shuffle( vcompass.begin(), vcompass.end(), rng );
        } else {
            break;
        }
    }
    for(int i = 0; i < 5; i++){
        chambers.emplace_back(new Chamber{i+1,numEne[i],vplayer[i],vcompass[i],vstair[i],numPotion[i],numGold[i],race,vsuite[i]});
        if (health != -1 ) chambers[playerChamber()]->getplayer()->setHealth(health);
    }
    passways= new Passways{};
    for(int h = 0; h < 25; h ++){
        string line;
        getline(in,line);
        map.emplace_back(vector<char>(79));
        for(int w = 0 ; w < 79; w++){
            map[h][w] = line[w];
        }
    }
    for (auto it: chambers) {
        if (it->getifplayer()) {
            map[it->getplayer()->getY()][it->getplayer()->getX()] = '@';
        }
        
        for (auto it2: it->getEnemies()) {
            map[it2->getY()][it2->getX()] = it->symbol(it2->getRace());
        }
        for (auto it3: it->getPotions()) {
            map[it3->getY()][it3->getX()] = 'P';
        }
        for (auto it4: it->getTreasure()) {
            if (DragonHorde* dh = dynamic_cast<DragonHorde*> (it4)) {
                if (dh->getBarrier()) {
                    map[dh->getY()][dh->getX()] = 'B';
                } else {
                    map[dh->getY()][dh->getX()] = 'G';
                }
            } else {
                map[it4->getY()][it4->getX()] = 'G';
            }
        }
    }
}

Floor::Floor(int health, char race, bool suite,ifstream& arg){
    Health = health;
    whichrace = race;
    ifBarrierSuite = suite;
    passways = new Passways();
    defaultArg(arg);
}

void Floor::defaultArg(ifstream& arg){
    for(int i = 0; i < 5 ; i++){
        chambers.emplace_back(new Chamber{});
        chambers[i]->setplayer(nullptr);
    }
    char cell = '!';
    //int rowplus = 0;
    //int colplus = 0;
    bool ifsetCompass = true;
    for(int ypos = 0; ypos < 25; ypos++) {
        map.emplace_back(vector<char>(79));
        for (int xpos = 0; xpos < 80; xpos++) {
            arg >> noskipws >> cell;
            map[ypos][xpos] = cell;
            int whichChamber = -1;
            if(xpos >=3 && xpos <=28 &&ypos >=3&& ypos <=6){
                whichChamber = 0;
            }else if ((ypos >=3 && ypos <=7) ||(ypos >=7 && ypos<=12 && xpos>=61 )){
                whichChamber = 1;
            }else if( xpos <= 49 && xpos >=38 && ypos <= 12 && ypos >= 10){
                whichChamber = 2;
            }else if (xpos >= 4 && xpos <= 24 && ypos >= 15 && ypos <=21){
                whichChamber = 3;
            }else {
                whichChamber = 4;
            }
            switch (cell)
            {
                case 'W':chambers[whichChamber]->createEnemy(xpos, ypos, 'w');
                    break;
                case 'V':chambers[whichChamber]->createEnemy(xpos, ypos, 'v');
                    break;
                case 'N':chambers[whichChamber]->createEnemy(xpos, ypos, 'g');
                    break;
                case 'T':chambers[whichChamber]->createEnemy(xpos, ypos, 't');
                    break;
                case 'X':chambers[whichChamber]->createEnemy(xpos, ypos, 'p');
                    break;
                case '8':chambers[whichChamber]->createEnemy(xpos, ypos, 'm');
                    break;
                case '5': chambers[whichChamber]->createPotion(xpos,ypos, "subDefence");
                    break;
                case '2': chambers[whichChamber]->createPotion(xpos,ypos, "addDefence");
                    break;
                case '4': chambers[whichChamber]->createPotion(xpos,ypos, "subAttack");
                    break;
                case '1': chambers[whichChamber]->createPotion(xpos,ypos, "addAttack");
                    break;
                case '3': chambers[whichChamber]->createPotion(xpos,ypos, "subHealth");
                    break;
                case '0': chambers[whichChamber]->createPotion(xpos,ypos, "addHealth");
                    break;
                case '6':chambers[whichChamber]->createGold(xpos,ypos,'n');
                    break;
                case '7':chambers[whichChamber]->createGold(xpos,ypos,'s');
                    break;
                case '9':
                if(ifBarrierSuite){
                    chambers[whichChamber]->setifsuite(true);
                    chambers[whichChamber]->createGold(xpos,ypos,'d');
                    ifBarrierSuite = false;
                }else {
                    chambers[whichChamber]->createGold(xpos,ypos,'d');
                }
                break;
                case '@':
                chambers[whichChamber]->createPlayer(xpos,ypos,whichrace);
                if (Health != -1) chambers[whichChamber]->getplayer()->setHealth(Health);
                break;    
                case '\\':
                chambers[whichChamber]->setstair(xpos,ypos);
                map[ypos][xpos] = '.';
                default:
                break;
            }
            if(chambers[whichChamber]->getEnemies().size() > 0 && ifsetCompass ){
                chambers[whichChamber]->getEnemies()[0]->setCompass(true);
                ifsetCompass = false;
            }
        }
        
    }
    for (auto it: chambers) {
        if (it->getplayer()) {
            if (it->getplayer()) {
            }
            map[it->getplayer()->getY()][it->getplayer()->getX()] = '@';
        }
        for (auto it2: it->getEnemies()) {
            map[it2->getY()][it2->getX()] = it->symbol(it2->getRace());
        }
        for (auto it3: it->getPotions()) {
            map[it3->getY()][it3->getX()] = 'P';
        }
        for (auto it4: it->getTreasure()) {
            if (DragonHorde* dh = dynamic_cast<DragonHorde*> (it4)) {
                if (dh->getBarrier()) {
                    map[dh->getY()][dh->getX()] = 'B';
                } else {
                    map[dh->getY()][dh->getX()] = 'G';
                }
            } else {
                map[it4->getY()][it4->getX()] = 'G';
            }
        }
    }
}

bool Floor::ifdoor(int x, int y) {
    if ((x == 4 && y == 29) || (x == 4 && y == 38) || (x == 7 && y == 43) || (x == 7 && y == 13) || (x == 9 && y == 43) ||
    (x == 11 && y == 60) || (x == 14 && y == 13) || (x == 13 && y == 43) || (x == 13 && y == 69) || (x == 15 && y == 69) ||
    (x == 18 && y == 43) || (x == 20 && y == 36) || (x == 20 && y == 25)) {
        return true;
    }
    return false;
}

int Floor::doorChamber(int x, int y) {
    if ((x == 4 && y == 29) || (x == 7 && y == 13)) return 0;
    if ((x == 4 && y == 38) || (x == 7 && y == 43) || (x == 11 && y == 60) || (x == 13 && y == 69)) return 1;
    if ((x == 13 && y == 43) || (x == 9 && y == 43)) return 2;
    if ((x == 14 && y == 13) || (x == 20 && y == 25)) return 3;
    if ((x == 15 && y == 69) || (x == 18 && y == 43) || (x == 20 && y == 36)) return 4;
    return -1;
}

void Floor::attack(int x, int y) {
    int enemy_x, enemy_y;
    int chamber_num;
    chamber_num = playerChamber();
    if (chamber_num == -1) return;
    int player_x = chambers[chamber_num]->getplayer()->getX();
    int player_y = chambers[chamber_num]->getplayer()->getY();
    enemy_x = player_x + x;
    enemy_y = player_y + y;
    vector<enemy*> enemies = chambers[chamber_num]->getEnemies();
    int round = 0;
    for (auto it = enemies.begin(); it != enemies.end(); ++it) {
        if ((*it)->getX() == enemy_x && (*it)->getY() == enemy_y) {
            if (chambers[chamber_num]->symbol((*it)->getRace()) == 'M') ifAttackMerchant = true;
            chambers[chamber_num]->getplayer()->attackEnemy(**it);
            if ((*it)->getHealth() != 0) {
                chambers[chamber_num]->getplayer()->attackby(**it);
                if (chambers[chamber_num]->getplayer()->getHealth() == 0) {
                    map[chambers[chamber_num]->getplayer()->getY()][chambers[chamber_num]->getplayer()->getX()] = '.';
                    return;
                }
            } else {
                if ((*it)->getifCompass()) {
                    //std::cout << "$$$$$" << std::endl;
                    map[(*it)->getY()][(*it)->getX()] = 'C';
                } else {
                    map[(*it)->getY()][(*it)->getX()] = '.';
                }
                if ((*it)->getRace() == CharType::Dragon) {
                    dragon* d = static_cast<dragon*>(*it);
                    vector <Treasure*> gold = chambers[chamber_num]->getTreasure();
                    for (auto it: gold) {
                        if (it->getX() == d->getHorde_x() && it->getY() == d->getHorde_y()) {
                            DragonHorde* dh = static_cast<DragonHorde*>(it);
                            dh->setState(false);
                        }
                    }
                }
                int old_amount = chambers[chamber_num]->getplayer()->getGold();
                int add = (*it)->getGold();
                //std::cout << "old gold" << old_amount << std::endl;
                chambers[chamber_num]->getplayer()->setGold(add + old_amount);
                //std::cout << "new gold" << chambers[chamber_num]->getplayer()->getGold() << std::endl;
                delete *it;
                //std::cout << enemies.size() << std::endl;
                enemies.erase(enemies.begin()+round);
                //(chambers[chamber_num]->getEnemies()).erase((chambers[chamber_num]->getEnemies()).begin()+round);
                //std::cout << enemies.size() << std::endl;
                chambers[chamber_num]->eraseEnemy(round);
                break;
            }
        }
        round += 1;
    }
}

void Floor::move(int x, int y) {
    //std::cout << "@@@@@" << std::endl;
    int chamber_num;
    chamber_num = playerChamber();
    //std::cout << chamber_num << std::endl;
    if (chamber_num == -1) {
        int old_x = passways->getplayer()->getX();
        int old_y = passways->getplayer()->getY();
        int new_x = old_x + x;
        int new_y = old_y + y;
        if (ifdoor(old_y, old_x)) {
           //std::cout << '#' << std::endl;
           if (map[new_y][new_x] != '#' && map[new_y][new_x] != '-' && map[new_y][new_x] != '|' && map[new_y][new_x] != ' ') {
              chamber_num = doorChamber(old_y, old_x);
              chambers[chamber_num]->setplayer(passways->getplayer());
              passways->setplayer(nullptr);
           }
       }
    }
    if (chamber_num == -1) {
        //std::cout << '1' << std::endl;
        vector<vector<int>> passway = passways->getposn();
        int old_x = passways->getplayer()->getX();
        int old_y = passways->getplayer()->getY();
        int new_x = old_x + x;
        int new_y = old_y + y;
        //std::cout << 'b' << std::endl;
        if (ifdoor(old_y, old_x) && map[new_y][new_x] == '#') {
            //std::cout << 'c' << std::endl;
            map[new_y][new_x] = '@';
            map[old_y][old_x] = '+';
            passways->getplayer()->setX(new_x);
            passways->getplayer()->setY(new_y);
            chamber_num = doorChamber(old_y, old_x);
            vector<enemy*> enemies = chambers[chamber_num]->getEnemies();
            for (auto it: enemies) {
                int ex = it->getX();
                int ey = it->getY();
                if (ifNeighbour(new_x, new_y, ex, ey)) {
                    passways->getplayer()->attackby(*it);
                }
            }
            return;
        }
        if (ifdoor(new_y, new_x)) {
            map[new_y][new_x] = '@';
            map[old_y][old_x] = '#';
            passways->getplayer()->setX(new_x);
            passways->getplayer()->setY(new_y);
            chamber_num = doorChamber(new_y, new_x);
            vector<enemy*> enemies = chambers[chamber_num]->getEnemies();
            for (auto it: enemies) {
                int ex = it->getX();
                int ey = it->getY();
                if (ifNeighbour(new_x, new_y, ex, ey)) {
                    passways->getplayer()->attackby(*it);
                }
            }
            return;
        }
        for (auto it: passway) {
            if (it[0] == new_x && it[1] == new_y) {
                if (ifdoor(old_y, old_x)) {
                    map[old_y][old_x] = '+';
                } else {
                    map[old_y][old_x] = '#';
                }
                map[new_y][new_x] = '@';
                passways->getplayer()->setX(new_x);
                passways->getplayer()->setY(new_y);
            }
        }
        //std::cout << '2' << std::endl;
    } else {
        //std::cout << playerChamber() << std::endl;
        //std::cout << "before attack " << chambers[playerChamber()]->getplayer()->getHealth() << std::endl;
        //std::cout << "$$$$$$$" << std::endl;
        int old_x = chambers[chamber_num]->getplayer()->getX();
        int old_y = chambers[chamber_num]->getplayer()->getY();
        //std::cout << old_x << ' ' << old_y << std::endl;
        int new_x = old_x + x;
        int new_y = old_y + y;
        char item = map[new_y][new_x];
        if (item != '.') {
            //std::cout << "123" << std::endl;
            //std::cout << '4' << std::endl;
            if (item == '+') {
                //std::cout << "456" << std::endl;
                //std::cout << "4a" << std::endl;
                vector<enemy*> enemies = chambers[chamber_num]->getEnemies();
                //std::cout << "5a" << std::endl;
                for (auto it: enemies) {
                if (it->getRace() == CharType::Merchant) continue;
                int ex = it->getX();
                int ey = it->getY();
                if (ifNeighbour(new_x, new_y, ex, ey)) {
                    //std::cout << "6a" << std::endl;
                    chambers[playerChamber()]->getplayer()->attackby(*it);
                    //std::cout << "7a" << std::endl;
                //std::cout << "after attack " << chambers[playerChamber()]->getplayer()->getHealth() << std::endl;
                    }
                }
                //if (chambers[chamber_num]->getplayer()) std::cout << "8a" << std::endl;
                passways->setplayer(chambers[chamber_num]->getplayer());
                //std::cout << "9a" << std::endl;
                chambers[chamber_num]->setplayer(nullptr);
                //std::cout << "789" << std::endl;
                //chambers[chamber_num]->setifplayer(false);
                passways->getplayer()->setX(new_x);
                passways->getplayer()->setY(new_y);
                //std::cout << "abc" << std::endl;
                map[old_y][old_x] = '.';
                map[new_y][new_x] = '@';
                //std::cout << "bcd" << std::endl;
                //std::cout << '5' << std::endl;
                return;
            } else if (item == 'G' || item == 'B') {
                //std::cout << '6' << std::endl;
                vector<Treasure*> gold = chambers[chamber_num]->getTreasure();
                int round = 0;
                for (auto const& it: gold) {
                    if (DragonHorde* dh = dynamic_cast<DragonHorde*> (it)) {
                        if (dh->getStatue()) continue;
                    }
                    if (it->getX() == new_x && it->getY() == new_y) {
                        if (item == 'B') {
                            chambers[chamber_num]->getplayer()->setifBarrier(true);
                        } else {
                            int old_amount = chambers[chamber_num]->getplayer()->getGold();
                            int add = it->getAmount();
                            //std::cout << "old gold" << old_amount << std::endl;
                            chambers[chamber_num]->getplayer()->setGold(add + old_amount);
                            //std::cout << "new gold" << chambers[chamber_num]->getplayer()->getGold() << std::endl;
                        }
                        map[old_y][old_x] = '.';
                        map[new_y][new_x] = '@';
                        chambers[chamber_num]->eraseGold(round);
                        chambers[chamber_num]->getplayer()->setX(new_x);
                        chambers[chamber_num]->getplayer()->setY(new_y);
                        break;
                    }
                    round += 1;
                }
                //std::cout << '7' << std::endl;
            } else if (item == 'C') {
                std::cout << '8' << std::endl;
                for (int i  = 0; i <= 4; i++){
                    std::cout << '9' << std::endl;
                    if(chambers[i]->getstairposn().y > 0){
                        std::cout << "10" << std::endl;
                        std::cout << chambers[i]->getstairposn().y << ' ' << chambers[i]->getstairposn().x << std::endl;
                        map[chambers[i]->getstairposn().y][chambers[i]->getstairposn().x] = '\\';
                        std::cout << "11" << std::endl;
                        if (chambers[i]->getstairposn().x > 0 && chambers[i]->getstairposn().y > 0) {
                            if (old_x != chambers[i]->getstairposn().x && old_y != chambers[i]->getstairposn().y) {
                             map[old_y][old_x] = '.';
                            }
                        } else {
                            map[old_y][old_x] = '.';
                        }
                        map[new_y][new_x] = '@';
                        chambers[chamber_num]->getplayer()->setX(new_x);
                        chambers[chamber_num]->getplayer()->setY(new_y);
                        break;
                    }
                }
                //map[chambers[chamber_num]->getstairposn().y][chambers[chamber_num]->getstairposn().x] = '\\';
                //map[old_y][old_x] = '.';
                //map[new_y][new_x] = '@';
                //std::cout << '9' << std::endl;
            }else if (item == 'P') {
                //std::cout << "%1" << std::endl;
                int count = 0;
                vector<Potion*> potions = chambers[chamber_num]->getPotions();
                for (auto it: potions) {
                    //std::cout << "%2" << std::endl;
                    if (it->getX() == new_x && it->getY() == new_y) {
                        it->enhance(chambers[chamber_num]->getplayer());
                        //std::cout << "%3" << std::endl;
                        delete it;
                        chambers[chamber_num]->erasePotion(count);;
                        usepotion = true;
                        //std::cout << "%4" << std::endl;
                        break;
                    }
                    count++;
                }
                map[old_y][old_x] = '.';
                map[new_y][new_x] = '@';
                //std::cout << "%5" << std::endl;
                chambers[chamber_num]->getplayer()->setX(new_x);
                chambers[chamber_num]->getplayer()->setY(new_y);
                //std::cout << "%6" << std::endl;
            } 
        } else {
            map[old_y][old_x] = '.';
            map[new_y][new_x] = '@';
            chambers[chamber_num]->getplayer()->setX(new_x);
            chambers[chamber_num]->getplayer()->setY(new_y);
            if (ifAttackMerchant) {
                if (map[new_y - 1][new_x - 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x - 1 && it->getY() == new_y - 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y - 1][new_x] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x && it->getY() == new_y - 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y - 1][new_x + 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x + 1 && it->getY() == new_y - 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y][new_x - 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x - 1 && it->getY() == new_y) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y][new_x + 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x + 1 && it->getY() == new_y) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y + 1][new_x - 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x - 1 && it->getY() == new_y + 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y + 1][new_x] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x && it->getY() == new_y + 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
                if (map[new_y + 1][new_x + 1] == 'M') {
                    for (auto it: chambers[chamber_num]->getEnemies()) {
                        if (it->getX() == new_x + 1 && it->getY() == new_y + 1) {
                            chambers[chamber_num]->getplayer()->attackby(*it);
                        }
                    }
                }
            }
        }
        //std::cout << "efg" << std::endl;
        if (ifdoor(old_y, old_x)) {
            if (!ifdoor(new_y, new_x)) {
                map[old_y][old_x] = '+';
          }
        }
        //std::cout << "hig" << std::endl;
        vector<enemy*> enemies = chambers[chamber_num]->getEnemies();
        for (auto it: enemies) {
            if (it->getRace() == CharType::Merchant) continue;
            int ex = it->getX();
            int ey = it->getY();
            if (ifNeighbour(new_x, new_y, ex, ey)) {
                chambers[playerChamber()]->getplayer()->attackby(*it);
                //std::cout << "after attack " << chambers[playerChamber()]->getplayer()->getHealth() << std::endl;
            }
        }
    }
    //std::cout << "finish" << std::endl;
}

void Floor::refresh() {
    //std::cout << "refresh " << chambers[playerChamber()]->getplayer()->getAttack() << std::endl;
    //std::cout << "refresh " << chambers[playerChamber()]->getplayer()->getHealth() << std::endl;
    vector<vector<int>> moved;
    for (int i = 0; i < 78; i++) {
        for (int j = 0; j < 24; j++) {
            vector<int> posn{i , j};
            for (int k = 0; k < 5; k++) {
                vector<enemy*> enemies = chambers[k]->getEnemies();
                for (auto it: enemies) {
                    int old_x = it->getX();
                    int old_y = it->getY();
                    if (old_x != i || old_y != j) continue;
                    bool member = false;
                    for (auto it: moved) {
                            if (it[0] == old_x && it[1] == old_y) {
                                member = true;
                            }
                        }
                        if (member) continue;
                    for(int i = 0; i < 50; i++) {
                        if (it->getRace() == CharType::Dragon) {
                          dragon* d = static_cast<dragon*>(it);
                          if (dragonblock(d->getX(), d->getY(), d->getHorde_x(), d->getHorde_y())) break;
                          d->dragonmove();
                      } else {
                        if (map[old_y - 1][old_x - 1] != '.' && map[old_y][old_x - 1] != '.' && map[old_y - 1][old_x] != '.' &&
                        map[old_y + 1][old_x + 1] != '.' && map[old_y][old_x + 1] != '.' && map[old_y + 1][old_x] != '.' && 
                        map[old_y + 1][old_x - 1] != '.' && map[old_y - 1][old_x + 1] != '.') break;
                          it->move();
                       }
                       if (map[it->getY()][it->getX()] == '.') {
                        if (chambers[k]->getstairposn().x == old_x && chambers[k]->getstairposn().y == old_y) continue;
                        map[it->getY()][it->getX()] = chambers[k]->symbol(it->getRace());
                        map[old_y][old_x] = '.'; 
                        vector<int> posn{it->getX(), it->getY()};
                        moved.emplace_back(posn);
                        //std::cout << it->getX() << " " << it->getY() << std::endl;
                        break;
                       }
                       it->setX(old_x);
                       it->setY(old_y);
                    }
                }
            }
        }
    }
}

void Floor::print() {
    for (auto row: map) {
        for (auto column: row) {
            cout << column;
        }
        cout << endl;
    }
}

bool Floor::ifnextfloor(int x, int y) {
    //std::cout << "R1" << std::endl;
    if (playerChamber() == -1) {
        return map[passways->getplayer()->getY()+y][passways->getplayer()->getX()+x] == '\\';
    } else {
        //std::cout << chambers[playerChamber()]->getplayer()->getY()+y << std::endl;
        //std::cout << chambers[playerChamber()]->getplayer()->getX()+x << std::endl;
        return map[chambers[playerChamber()]->getplayer()->getY()+y][chambers[playerChamber()]->getplayer()->getX()+x] == '\\';
       //std::cout << "R2" << std::endl;
    }
}

 int Floor::playerChamber() {
    //std::cout << "R3" << std::endl;
    for (int i = 0; i < 5; i++) {
        if (chambers[i]->getplayer()) {
            //std::cout << i << std::endl;
            return i;
        }
    }
    //std::cout << "R4" << std::endl;
    return -1;
}

bool Floor::ifPotion(int x, int y) {
    if (!chambers[playerChamber()]->getplayer()) {
        return map[passways->getplayer()->getY()+y][passways->getplayer()->getX()+x] == 'P';
    } else {
        return map[chambers[playerChamber()]->getplayer()->getY()+y][chambers[playerChamber()]->getplayer()->getX()+x] == 'P';
    }
}

void Floor::setMap(int x, int y, char symbol) {
    map[y][x] = symbol;
}

bool Floor::ifAlive() {
    //std::cout << "alive" << playerChamber() << std::endl;
    if (playerChamber() == -1) {
        //std::cout << passways->getplayer()->getHealth() << std::endl;
        return passways->getplayer()->getHealth() != 0;
    }
    //std::cout << chambers[playerChamber()]->getplayer()->getHealth() << std::endl;
    return chambers[playerChamber()]->getplayer()->getHealth() != 0;
}

bool Floor::dragonblock(int x, int y, int hx, int hy) {
    if (hx - x == 1 && hy - y == 1) {
        if (map[y+1][x] != '.' &&  map[y][x+1] != '.') return true;
    } else if (hx - x == 1 && hy - y == -1) {
        if (map[y-1][x] != '.' &&  map[y][x+1] != '.') return true;
    } else if (hx - x == -1 && hy - y == 1) {
        if (map[y+1][x] != '.' &&  map[y][x-1] != '.') return true;
    } else if (hx - x == -1 && hy - y == -1) {
        if (map[y-1][x] != '.' &&  map[y][x-1] != '.') return true;
    } else if (hx - x == 0 && hy - y == 1) {
        if (map[y][x+1] != '.' &&  map[y][x-1] != '.' && map[y+1][x-1] != '.' && map[y+1][x+1] != '.' ) return true;
    } else if (hx - x == 1 && hy - y == 0) {
        if (map[y+1][x] != '.' &&  map[y-1][x] != '.' && map[y+1][x+1] != '.' && map[y-1][x+1] != '.' ) return true;
    } else if (hx - x == -1 && hy - y == 0) {
        if (map[y+1][x] != '.' &&  map[y-1][x] != '.' && map[y+1][x-1] != '.' && map[y-1][x-1] != '.' ) return true;
    } else if (hx - x == 0 && hy - y == -1) {
        if (map[y][x+1] != '.' &&  map[y][x-1] != '.' && map[y-1][x+1] != '.' && map[y-1][x-1] != '.' ) return true;
    }
    return false;
}

Floor::~Floor(){
}

bool Floor::ifNeighbour(int px, int py, int x, int y) {
    if (abs(px - x) <= 1 && abs(py- y) <= 1) {
        return true;
    } else {
        return false;
    }
}

void Floor::printMessage(int floornum) {
    char r = this->whichrace;
    std::string printrace;
    if (r == 'h') {
        printrace = "Human";
    } else if (r == 'e') {
        printrace = "Elves";
    } else if (r == 'd') {
        printrace = "Dwarf";
    } else {
        printrace = "Orc";
    }
    int chanum = playerChamber();
    if (chanum == -1) {
        if (passways->getplayer()->getRace() == CharType::Dwarf) {
            std::cout << "Gold will be doubled since player is a dwarf" << std::endl;
        } else if (passways->getplayer()->getRace() == CharType::Orc) {
            std::cout << "Gold will be reduced to half since player is an orc" << std::endl;
        } 
        int hp = passways->getplayer()->getHealth();
        int at = passways->getplayer()->getAttack();
        int df = passways->getplayer()->getDefence();
        std::cout << "HP: " << hp << std::endl;
        std::cout << "Atk: " << at << std::endl;
        std::cout << "Def: " << df << std::endl;
        if (ifdoor(passways->getplayer()->getY(), passways->getplayer()->getX())) {
            std::cout << "Action: " << "Player is at a door" << std::endl;
        } else {
            std::cout << "Action: " << "Player is in the passwasy" << std::endl;
        }
        return;
    }
    int gnum = chambers[chanum]->getplayer()->getGold();
    std::cout << "Race: " << printrace << " Gold: " << gnum;
    for (int i = 0; i < 56; i++) {
        std::cout << ' ';
    }
    std::cout << "Floor: " << floornum << std::endl; 
    if (chambers[chanum]->getplayer()->getRace() == CharType::Dwarf) {
        std::cout << "Gold will be doubled since player is a dwarf" << std::endl;
    } else if (chambers[chanum]->getplayer()->getRace() == CharType::Orc) {
        std::cout << "Gold will be reduced to half since player is an orc" << std::endl;
    }   
    int hp = chambers[chanum]->getplayer()->getHealth();
    int at = chambers[chanum]->getplayer()->getAttack();
    int df = chambers[chanum]->getplayer()->getDefence();
    bool ia = chambers[chanum]->getplayer()->getunderattack();
    std::cout << "HP: " << hp << std::endl;
    std::cout << "Atk: " << at << std::endl;
    std::cout << "Def: " << df << std::endl;
    if (recordHp.size() == 0) {
        //std::cout << "when hp size is 0" << std::endl;
        if (chambers[chanum]->getplayer()->getRace() == CharType::Human) {
            recordingHp(140);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Elf) {
            recordingHp(140);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Dwarf) {
            recordingHp(100);
        } else {
            recordingHp(180);
        }
    }

    if (recordAt.size() == 0) {
        //std::cout << "when at size is 0" << std::endl;
        if (chambers[chanum]->getplayer()->getRace() == CharType::Human) {
            recordingAt(20);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Elf) {
            recordingAt(30);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Dwarf) {
            recordingAt(20);
        } else {
            recordingAt(30);
        }
    }

    if (recordDf.size() == 0) {
        //std::cout << "when df size is 0" << std::endl;
        if (chambers[chanum]->getplayer()->getRace() == CharType::Human) {
            recordingDf(20);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Elf) {
            recordingDf(10);
        } else if (chambers[chanum]->getplayer()->getRace() == CharType::Dwarf) {
            recordingDf(30);
        } else {
            recordingDf(25);
        }
    }

    //std::cout << librarianHp << std::endl;
    //std::cout << recordHp.size() << std::endl;
    //std::cout << recordHp[librarianHp] << std::endl;
    if (hp == recordHp[librarianHp] && at == recordAt[librarianAt] && df == recordDf[librarianDf] && usepotion) {
        std::cout << "Action: " << "PC uses RH" << std::endl; 
        usepotion = false;
    }

    if (hp < recordHp[librarianHp]) {
        //std::cout << "in" << df << std::endl;
        if (ia) {
            std::cout << "Action: " << "PC get attacked, " << recordHp[librarianHp] - hp << " damage dealt" << std::endl;
            chambers[chanum]->getplayer()->setunderattack(false);
        } else {
            std::cout << "Action: " << "PC uses PH" << std::endl; 
        }
    }
    if (hp > recordHp[librarianHp]) {
        std::cout << "Action: " << "PC uses RH" << std::endl; 
    }

    if (at < recordAt[librarianAt]) {
        std::cout << "Action: " << "PC uses WA" << std::endl; 
    }
    if (at > recordAt[librarianAt]) {
        std::cout << "Action: " << "PC uses BA" << std::endl; 
    }

    if (df < recordDf[librarianDf]) {
        std::cout << "Action: " << "PC uses WD" << std::endl; 
    }
    if (df > recordDf[librarianDf]) {
        std::cout << "Action: " << "PC uses BD" << std::endl; 
    }
    librarianHp += 1;
    librarianAt += 1;
    librarianDf += 1;
    recordingHp(hp);
    recordingAt(at);
    recordingDf(df);
    usepotion = false;
}


void Floor::recordingHp(int a) {
    recordHp.emplace_back(a);
}

void Floor::recordingAt(int b) {
    recordAt.emplace_back(b);
}

void Floor::recordingDf(int c) {
    recordDf.emplace_back(c);
}

void Floor::printscore() {
    int chamber_num = playerChamber();
    int gold;
    CharType race;
    std::cout << "//////////Game Over//////////" << std::endl;
    if (chamber_num == -1) {
        gold = passways->getplayer()->getGold();
        race = passways->getplayer()->getRace();
    } else {
        gold = chambers[chamber_num]->getplayer()->getGold();
        race = chambers[chamber_num]->getplayer()->getRace();
    }
    std::cout << "The amount of gold collected is " << gold << std::endl;
    if (race == CharType::Dwarf) {
        gold *= 2;
        std::cout << "Since player race is Dwarf, gold is doubled, new amount is " << gold << std::endl;
    } else if (race == CharType::Orc) {
        gold /= 2;
        std::cout << "Since player race is Orc, gold is reduced to half, new amount is " << gold << std::endl;
    }
    std::cout << "The score determined by gold is " << gold << std::endl;
    if (race == CharType::Human) {
        std::cout << "Since player race is Human, score is doubled, the final score is " << gold*2 << std::endl;
    } 
}

int Floor::getHealth() {
    return Health;
}


