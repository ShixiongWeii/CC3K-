#include "enemyFactory.h"

enemy* enemyFactory::createWerewolf(int x, int y, bool ifCompass) {
    return new werewolf(x, y, ifCompass);
}

enemy* enemyFactory::createVampire(int x, int y, bool ifCompass) {
    return new vampire(x, y, ifCompass);
}

enemy* enemyFactory::createGoblin(int x, int y, bool ifCompass) {
    return new goblin(x, y, ifCompass);
}

enemy* enemyFactory::createTroll(int x, int y, bool ifCompass) {
    return new troll(x, y, ifCompass);
}

enemy* enemyFactory::createPhoenix(int x, int y, bool ifCompass) {
    return new phoenix(x, y, ifCompass);
}

enemy* enemyFactory::createMerchant(int x, int y, bool ifCompass) {
    return new merchant(x, y, ifCompass);
}

enemy* enemyFactory::createDragon(int x, int y, bool ifCompass, int horde_x, int horde_y) {
    return new dragon(x, y, ifCompass, horde_x, horde_y);
}

