CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = cc3k
OBJECTS = cc3k.o main.o character.o chamber.o floor.o dragon.o dwarf.o elf.o enemy.o goblin.o human.o merchant.o orc.o phoenix.o player.o troll.o vampire.o werewolf.o enemyFactory.o playerFactory.o attackpotion.o basepotion.o decorator.o defencepotion.o treasure.o dragonhorde.o normal.o small.o healthpotion.o passway.o  
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
