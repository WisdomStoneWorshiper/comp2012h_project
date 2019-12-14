#ifndef CHARACTER_H
#define CHARACTER_H

#endif // CHARACTER_H
#include "property.h"

using namespace std;

class Character
{
private:
    vector <unsigned> owned_place_id_list;
    const unsigned short id;
    enum STATE{NORMAL, IMPRISONMENT};
    unsigned short position;
    bool jail_pass;
    bool inJail;
    int money;
    STATE state;
    QString user_name;
    unsigned numOfRestaurant;
    int jailDiceCount[2];
    QMessageBox msgBox;
    bool losed;

public:
    Character(unsigned short, QString name);
    Character(const Character&);

    unsigned short getId() const;
    vector <unsigned> getOwnedPropertyList() const;
    int getMoney() const;
    void setmoney(int);
    bool getJailPass() const;
    QString getName() const;
    unsigned short getPosition() const;
    void setPosition(unsigned);
    void addProperty(Property*);
    void removeProperty(Property*);
    bool buyProperty(Property*);
    void changeJailPass();
    bool checkInJail();
    void setinJail(bool);
    Character& operator+=(int);
    Character& operator-=(int);

    void setState(STATE);
    unsigned getNumOfRestaurant() const;
    void setNumOfRestaurant(unsigned);
    void saveJailDice(unsigned);
    QString getPlayerInfo();
    bool checkLosed();
    void setLosed();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
};
