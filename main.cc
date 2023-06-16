#include "cc3k.h"
#include <fstream>
#include <string>
using namespace std;

std::vector<int> direction(char a, char b) {
    int x;
    int y;
    int success = 1;
    if (a == 'n' && b == 'o') {
        x = -1;
        y = 0;
    } else if (a == 's' && b == 'o') {
        x = 1;
        y = 0;
    } else if (a == 'e' && b == 'a') {
        x = 0;
        y = 1;
    } else if (a == 'w' && b == 'e') {
        x = 0;
        y = -1;
    } else if (a == 'n' && b == 'e') {
        x = -1;
        y = 1;
    } else if (a == 'n' && b == 'w') {
        x = -1;
        y = -1;
    } else if (a == 's' && b == 'e') {
        x = 1;
        y = 1;
    } else if (a == 's' && b == 'w') {
        x = 1;
        y = -1;
    } else {
        success = 0;
    }
    std::vector<int> result{y, x, success};
    return result;
}

int main( int argc, char** argv) {
    char race; 
    int numfloor = 1;
    //std::cout << "就你叫segmentation faultnoknow"  << std::endl;
    cc3k game{};
    bool ifdefault = true;
    int barrier = game.random();
    char cmd;
    std::cin >> cmd;
    //std::cout << "就你叫segmentation faultwhy"  << std::endl;
    while (cmd != 'h' && cmd != 'e' && cmd != 'd' && cmd != 'o') {
        if (cmd == 'q') return 0;
        std::cout << "Please select player race:" << std::endl;
        std::cin >> cmd;
    }
    if (cmd == 'q') return 0;
    //std::cout << "就你叫segmentation fault啊前"  << std::endl;
    if (argc > 1) {
        //std::cout << "define map ifs" << std::endl;
        ifdefault = false;
        ifstream map(argv[1]);
        //std::cout << "define done" << std::endl;
        game.initinput(cmd, map, -1);
    } else {
        //std::cout << "就你叫segmentation fault啊deafultbefore"  << std::endl;
        game.initdefault(cmd, numfloor, barrier, -1);
        //std::cout << "就你叫segmentation fault啊defaultafter"  << std::endl;
    }
    /*while (map.is_open()) {
        char add = '@';
        while (map >> add) {
            std::cout << add << std::endl;
        }
        map.close();
    }*/
    //std::cout << "cout done" << std::endl;

    /*if (ifdefault == false) {
        //std::cout << "1" << std::endl;
        game.initinput(cmd, numfloor, barrier, map);
        //std::cout << "2" << std::endl;
    } else {
        game.initdefault(cmd);
    }*/
    race = cmd;
    game.print();
    game.pprr(numfloor);
    char northSouth;
    char eastWest;
    while (std::cin >> cmd) {
        if (cmd == 'r') {
            game.reset();
            //if (!std::cin >> cmd)  return 1;
            std::cin >> cmd;
            while (cmd != 'h' && cmd != 'e' && cmd != 'd' && cmd != 'o') {
                std::cout << "Please select player race:" << std::endl;
                std::cin >> cmd;
            }
            numfloor = 1;
            barrier = game.random();
            if (ifdefault == false) {
                ifstream map(argv[1]);
                game.initinput( cmd, map, -1);
            } else {
                //std::cout << "就你叫segmentation fault啊deafultbefore"  << std::endl;
                game.initdefault(cmd, numfloor, barrier, -1);
                //std::cout << "就你叫segmentation fault啊defaultafter"  << std::endl;
            }
            race = cmd;
        } else if (cmd == 'u') {
            //if (!(std::cin >> northSouth >> eastWest)) return 1;
            std::cin >> northSouth >> eastWest;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) {
                std::cout << "invalid move" << std::endl;
                continue;
            }
            if (!game.ifPotion(result[0], result[1])) continue;
            game.move(result[0], result[1]);
            game.refresh();
        } else if (cmd == 'a') {
            //if (!(std::cin >> northSouth >> eastWest)) return 1;
            std::cin >> northSouth >> eastWest;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) {
                std::cout << "invalid move" << std::endl;
                continue;
            }
            game.attack(result[0], result[1]);
            game.refresh();
        } else if (cmd == 'q') {
            return 0;
        } else {
            //if (!(std::cin >> northSouth >> eastWest)) return 1;
            northSouth = cmd;
            std::cin >> eastWest;
            vector<int> result = direction(northSouth, eastWest);
            if (!result[2]) {
                std::cout << "invalid move" << std::endl;
                continue;
            }
            if (game.ifnextfloor(result[0], result[1])) {
                if (numfloor == 5) {
                    game.printscore();
                    return 0;
                } else {
                    int health = game.getHealth();
                    game.reset();
                    if (ifdefault == false) {
                    ifstream map(argv[1]);
                    //std::cout << "&&&&&" << std::endl;
                    game.initinput(race,map, health);
                    //std::cout << "*****" << std::endl;
                     } else {
                    game.initdefault(race , numfloor, barrier, health);
                    }
                    numfloor += 1;
                    game.print();
                    game.pprr(numfloor);
                    continue;
                }
            }
            game.move(result[0], result[1]);
            game.refresh();
        }
        if (!game.ifAlive()) {
            std::cout << "Player dies" << std::endl;
            return 0;
        }
        game.print();
        game.pprr(numfloor);
    }
}



