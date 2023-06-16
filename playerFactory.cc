#include "playerFactory.h"

player* playerFactory::createHuman(int x, int y) {
        return new human(x, y);
    }

player* playerFactory::createElf(int x, int y) {
        return new elf(x, y);
    }

player* playerFactory::createDwarf(int x, int y) {
        return new dwarf(x, y);
    }

player* playerFactory::createOrc(int x, int y) {
        return new orc(x, y);
    }



