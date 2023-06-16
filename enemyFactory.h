#ifndef _ENEMYF_
#define _ENEMYF_
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "merchant.h"
#include "dragon.h"

class enemy;

class enemyFactory {
public:
  enemy* createWerewolf(int x, int y, bool ifCompass);
  enemy* createVampire(int x, int y, bool ifCompass);
  enemy* createGoblin(int x, int y, bool ifCompass);
  enemy* createTroll(int x, int y, bool ifCompass);
  enemy* createPhoenix(int x, int y, bool ifCompass);
  enemy* createMerchant(int x, int y, bool ifCompass);
  enemy* createDragon(int x, int y, bool ifCompass, int horde_x, int horde_y);
};

#endif

