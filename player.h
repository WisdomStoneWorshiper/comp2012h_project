#ifndef PLAYER_H
#define PLAYER_H

#include "charactor.h"
#include "QString"
using namespace std;

class Player : public Charactor{

public:
    Player(unsigned short, QString);
    Player(const Player&);
    float getGpa() const;
    int getMoney() const;
    bool getJailPass() const;
    QString getName() const;
    bool buyProperty(Property*);
    Player& operator+(int);
    Player& operator-(int);

private:
    enum SCHOOL{ENGINEERING,SCIENCE,BUSSINESS, HUMANITIES};
    enum STATE{NORMAL, IMPRISONMENT};
    bool jail_pass;
    float gpa;
    int money;
    SCHOOL school;
    STATE state;
    QString user_name;

};

#endif // PLAYER_H
