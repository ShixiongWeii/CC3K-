#include "enemy.h"
using namespace std;

enemy::enemy(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass): character(race, health, attack, defence, gold,
  x, y, ifCompass) {}

void enemy::move() {
  bool failure = true;
  while(failure) {
    std::vector<int> east_west = { 0, 1, -1 };
    std::vector<int> north_south = { 0, 1, -1 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( east_west.begin(), east_west.end(), rng );
    std::shuffle( north_south.begin(), north_south.end(), rng );
    if (east_west[0] == 0 && north_south[0] == 0) continue;
    x += east_west[0];
    y += north_south[0];
    failure = false;
  }
}

enemy::~enemy() {};
