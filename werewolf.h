#ifndef _WEREWOLF_
#define _WEREWOLF_
#include "enemy.h"

class werewolf: public enemy {
  werewolf(int x, int y, bool ifCompass);
  friend class enemyFactory;
};

#endif


