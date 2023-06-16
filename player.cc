#include "player.h"
using namespace std;

player::player(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass): character(race, health, attack, defence, gold,
  x, y, ifCompass) {
    //std::cout  << "player constructor" << health << std::endl;
  }

void player::enhanceAttack(int new_attack) {
  attack = new_attack;
  //std::cout << "New attack" << new_attack << std::endl;
}

void player::enhanceDefence(int new_defence) {
  defence = new_defence;
  //std::cout << "New defence" << new_defence << std::endl;
}

void player::attackby(enemy& enemy) {
  //std::cout << "player " << health << std::endl;
  int damage; 
  damage = ceil(100 * enemy.getAttack()/(100 + defence));
  //std::cout << "damage " << damage << std::endl;
  if (ifBarrier == true) damage = ceil(damage / 2);
  health -= damage;
  //std::cout << "player " << health << std::endl;
  if (health < 0) health = 0;
  //std::cout << "player " << health << std::endl;
  underattack = true;
}

void player::attackEnemy(enemy& enemy) {
  int damage;
  damage = ceil(100 * attack/(100 + enemy.getDefence()));
  int enemy_health = enemy.getHealth() - damage;
  //std::cout << "enemy "<< enemy_health << std::endl;
  if (enemy_health < 0) enemy_health = 0;
  //std::cout << "enemy "<< enemy_health << std::endl;
  enemy.setHealth(enemy_health);
}

bool player::getifBarrier() {
  return ifBarrier;
}

void player::setifBarrier(bool change) {
  ifBarrier = change;
}

void player::enhanceHealth(int new_health) {
    health = new_health;
    //std::cout << "New health" << new_health << std::endl;
}

void player::setunderattack(bool a) {
  underattack = a;
}

bool player::getunderattack() {
  return underattack;
}

player::~player() {}


