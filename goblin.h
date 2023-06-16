#ifndef _GOBLIN_
#define _GOBLIN_
#include "enemy.h"

class goblin: public enemy {
  goblin(int x, int y, bool ifCompass);
  friend class enemyFactory;
};

#endif
