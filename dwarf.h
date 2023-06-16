#ifndef _DWARF_
#define _DWARF_
#include "player.h"

class dwarf: public player {
  dwarf(int x, int y);
  friend class playerFactory;
};

#endif
