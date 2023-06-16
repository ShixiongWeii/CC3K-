#ifndef _HUMAN_
#define _HUMAN_
#include "player.h"

class human: public player {
  human(int x, int y);
  friend class playerFactory;
};

#endif

