#ifndef _ENEMY_
#define _ENEMY_
#include "character.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class enemy : public character {
public:
  enemy(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass);
  void move();
  ~enemy();
};

#endif
