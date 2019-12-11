#ifndef PLAYER_H
#define PLAYER_H

#include "charactor.h"
#include "QString"
using namespace std;

class Player : public Charactor{


private:
    enum SCHOOL{ENGINEERING,SCIENCE,BUSSINESS, HUMANITIES};
    enum STATE{NORMAL, IMPRISONMENT};
    unsigned short position;
    bool jail_pass, inJail;
    float gpa;
    int money;
    SCHOOL school;
    STATE state;
    QString user_name;

public:

    Player(unsigned short, QString);
    Player(const Player&);
    float getGpa() const;
    int getMoney() const;
    bool getJailPass() const;
    QString getName() const;
    bool buyProperty(Property*);
    void changeJailPass();
    unsigned short getPosition() const;
    void setPosition(unsigned short);
    Player& operator+=(int);
    Player& operator-=(int);
    bool checkInJail();
    void setinJail(bool);
    void setGpa(float);
    void setmoney(int);
    void setState(STATE);
    void setSchool(SCHOOL);

};

#endif // PLAYER_H
