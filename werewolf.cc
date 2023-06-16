#include "werewolf.h"

werewolf::werewolf(int x, int y, bool ifCompass): 
    enemy(CharType::Werewolf, 120, 30, 5, 1, x, y, ifCompass) {}



