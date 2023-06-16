#ifndef _DRAGON_
#define _DRAGON_
#include "enemy.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class dragon: public enemy {
  int horde_x, horde_y;
  dragon(int x, int y, bool ifCompass, int horde_x, int horde_y);
  friend class enemyFactory;
public:
  void dragonmove();
  int getHorde_x();
  int getHorde_y();
};

#endif
