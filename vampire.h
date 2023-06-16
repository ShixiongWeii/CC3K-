#ifndef _VAMPIRE_
#define _VAMPIRE_
#include "enemy.h"

class vampire: public enemy {
  vampire(int x, int y, bool ifCompass);
  friend class enemyFactory;
};

#endif

