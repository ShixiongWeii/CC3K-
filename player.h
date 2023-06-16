
#ifndef _PLAYER_
#define _PLAYER_
#include "character.h"
#include "enemy.h"
#include <tgmath.h>

class player : public character {
  bool ifBarrier = false;
  bool underattack = false;
public:
  player(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass);
  void enhanceAttack(int new_attack);
  void enhanceDefence(int new_defence);
  void enhanceHealth(int new_health);
  void attackby( enemy& );
  void attackEnemy( enemy& );
  bool getifBarrier();
  void setifBarrier(bool);
  void setunderattack(bool);
  bool getunderattack();
  ~player();
};

#endif

