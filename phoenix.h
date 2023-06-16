#ifndef _PHOENIX_
#define _PHOENIX_
#include "enemy.h"

class phoenix: public enemy {
  phoenix(int x, int y, bool ifCompass);
  friend class enemyFactory;
};

#endif


