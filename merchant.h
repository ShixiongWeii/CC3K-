#ifndef _MERCHANT_
#define _MERCHANT_
#include "enemy.h"

class merchant: public enemy {
  merchant(int x, int y, bool ifCompass);
  friend class enemyFactory;
  bool ifAttack;
};

#endif

