#ifndef _TROLL_
#define _TROLL_
#include "enemy.h"

class troll: public enemy {
  troll(int x, int y, bool ifCompass);
  friend class enemyFactory;
};

#endif

