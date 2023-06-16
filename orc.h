#ifndef _ORC_
#define _ORC_
#include "player.h"

class orc: public player {
  orc(int x, int y);
  friend class playerFactory;
};

#endif

