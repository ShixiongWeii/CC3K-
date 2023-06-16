#ifndef _CHARACTER_
#define _CHARACTER_
#include <string>

enum class CharType { Human, Elf, Dwarf, Orc, Werewolf, Vampire, Goblin, Troll, Phoenix, Merchant, Dragon };

class character {
protected:
  CharType race;
  int health;
  int attack;
  int defence;
  int gold;
  int x;
  int y;
  bool ifCompass;
public:
  character(CharType race, int health, int attack, int defence, int gold,
  int x, int y, bool ifCompass);
  CharType getRace() const;
  int getHealth() const;
  int getAttack() const;
  int getDefence() const;
  int getGold() const;
  int getX() const;
  int getY() const;
  bool getifCompass() const;
  void setRace(CharType race);
  void setHealth(int health);
  void setAttack(int attack);
  void setDefence(int defence);
  void setGold(int gold);
  void setX(int x);
  void setY(int y);
  void setCompass(bool ifCompass);
  
  ~character();
};

#endif

