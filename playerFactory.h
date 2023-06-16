#ifndef _PLAYERF_
#define _PLAYERF_
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"

class player;

class playerFactory {
public:
  player* createHuman(int x, int y);
  player* createElf(int x, int y);
  player* createDwarf(int x, int y);
  player* createOrc(int x, int y);
};

#endif

