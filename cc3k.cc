#include "cc3k.h"

cc3k::cc3k(): board{nullptr} {}

void cc3k::reset() {
    delete board;
    board = nullptr;
}

void cc3k::attack(int x, int y) {
    board->attack(x, y);
}

void cc3k::move(int x, int y) {
    board->move(x, y);
}

void cc3k::print() {
    board->print();
}

void cc3k::refresh() {
    board->refresh();
}

bool cc3k::ifnextfloor(int x, int y) {
    return board->ifnextfloor(x, y);
}

bool cc3k::ifPotion(int x, int y) {
    return board->ifPotion(x, y);
}

void cc3k::initdefault(char race, int numfloor, int barrier, int health) {
    if (numfloor == barrier) {
        board = new Floor(health, race, true);
    } else {
        board = new Floor(health, race, false);
    }
}

void cc3k::initinput(char race, ifstream& map, int health) {
    board = new Floor(health, race, false, map);
}

int cc3k::random() {
    std::vector<int> chambernum = { 1, 2, 3, 4, 5 };
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( chambernum.begin(), chambernum.end(), rng );
    return chambernum[0];
}
bool cc3k::ifAlive() {
    return board->ifAlive();
}

void cc3k::pprr(int numfloor) {
    board->printMessage(numfloor);
}

void cc3k::userechp(int maxhp) {
    board->recordingHp(maxhp);
}
void cc3k::userecat(int maxat) {
    board->recordingAt(maxat);
}
void cc3k::userecdf(int maxdf) {
    board->recordingDf(maxdf);
}

int cc3k::getHealth() {
    return board->getHealth();
}
void cc3k::printscore() {
    board->printscore();
}
cc3k::~cc3k() {
    delete board;
}
