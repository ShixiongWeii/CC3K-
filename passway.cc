#include "passway.h"
#include <iostream>
#include <vector>

using namespace std;
/*
if(num == 0){
        for(int c = 30; c <37; c++ ){
            for (int r = 8; r < 13; r++){
            vector<int> vect = {c,}
            posn.emplace_back(vec<)
            }
        }
    }
    */

vector<vector <int> > Passways::getposn(){
    return posn;
}
player* Passways::getplayer(){
    return curplayer;
}
Passways::Passways(){
    
        for(int i = 8; i <= 13; i ++){
            vector<int> vect {13,i};
            posn.emplace_back(vect);
        }
    
        for(int i = 8; i <= 20; i ++){
            vector<int> vect {31,i};
            posn.emplace_back(vect);
        }
    
        for(int i = 4; i <= 8; i ++){
            vector<int> vect {33,i};
            posn.emplace_back(vect);
        }
        /*
        vector<vector<int>> vect{{33,4},{33,5},{33,6},{33,7},{33,8}};
        posn = vect;
        */
    
        for(int i = 14; i <= 17; i ++){
            vector<int> vect {43,i};
            posn.emplace_back(vect);
        }
    
        for(int i = 11; i <= 16; i ++){
            vector<int> vect {54,i};
            posn.emplace_back(vect);
        }
    
        vector<int> vect {69,14};
        posn.emplace_back(vect);
   
        for(int i = 30; i <= 37; i ++){
            vector<int> vect {i,4};
            posn.emplace_back(vect);
        }
    
        for(int i = 31; i <= 43; i ++){
            vector<int> vect {i,8};
            posn.emplace_back(vect);
        }
    
        for(int i = 13; i <= 31; i ++){
            vector<int> vect {i,11};
            posn.emplace_back(vect);
        }
    
        for(int i = 54; i <= 59; i ++){
            vector<int> vect {i,11};
            posn.emplace_back(vect);
        }
    
        for(int i = 31; i <= 54; i ++){
            vector<int> vect {i,16};
            posn.emplace_back(vect);
        }
    
        for(int i = 26; i <= 35; i ++){
            vector<int> vect {i,20};
            posn.emplace_back(vect);
        }
    
}

void Passways::setplayer(player* newplayer) {
    curplayer = newplayer;
}

Passways::~Passways(){};


