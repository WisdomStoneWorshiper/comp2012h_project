#ifndef PLAYER_H
#define PLAYER_H

#include "charactor.h"

using namespace std;

class Player : public Charactor{

public:
    Player(unsigned short);
    Player(Player&);
<<<<<<< HEAD
=======

>>>>>>> 2e75d4f210f0d071075799ac69daeb3830c4e57d
    float getGpa();
    int getMoney();
    bool getJailPass();
    bool buyProperty(Property*);

    Player& operator+(int);
    Player& operator-(int);

private:
    enum SCHOOL{ENGINEERING,SCIENCE,BUSSINESS, HUMANITIES};
    enum STATE{NORMAL, IMPRISONMENT};
    bool jail_pass;
    unsigned short position;
    float gpa;
    int money;
    SCHOOL school;
    STATE state;

};

#endif // PLAYER_H
