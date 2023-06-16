#ifndef _ELF_
#define _ELF_
#include "player.h"

class elf: public player {
  elf(int x, int y);
  friend class playerFactory;
};

#endif
