#include "character.h"

character::character(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass): race{race}, health{health}, attack{attack}, defence{defence},
  gold{gold}, x{x}, y{y}, ifCompass{ifCompass} {}

CharType character::getRace() const{
    return race;
}

int character::getHealth() const {
    return health;
}
int character::getAttack() const {
    return attack;
}

int character::getDefence() const {
    return defence;
}

int character::getGold() const {
    return gold;
}
int character::getX() const {
    return x;
}
int character::getY() const {
    return y;
}
bool character::getifCompass() const {
    return ifCompass;
}

void character::setRace(CharType race) {
    this->race = race;
}

void character::setHealth(int health) {
    this->health = health;
}
void character::setAttack(int attack) {
    this->attack = attack;
}

void character::setDefence(int defence) {
    this->defence = defence;
}

void character::setGold(int gold) {
    this->gold = gold;
}
void character::setX(int x) {
    this->x = x;
}
void character::setY(int y) {
    this->y = y;
}
void character::setCompass(bool ifCompass) {
    this->ifCompass = ifCompass;
}

character::~character() {}

