#ifndef PLAYER_H
#define PLAYER_H

#include "charactor.h"

using namespace std;

class Player: public Charactor{

public:
    Player(const unsigned short);
    int get_position();
    float get_gpa();
    int get_money();
    Player& operator+(int);
    Player& operator-(int);

private:
    enum SCHOOL{ENGINEERING,SCIENCE,BUSSINESS, HUMANITIES};
    enum STATE{NORMAL, IMPRISONMENT};
    unsigned short position;
    unsigned short id;
    float gpa;
    int money;
    SCHOOL school;
    STATE state;

};

#endif // PLAYER_H
