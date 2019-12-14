#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QMessageBox>
#include <list>
#include <QGraphicsPixmapItem>
#include "property.h"

using namespace std;

class Player: public QGraphicsPixmapItem{


private:
    vector <unsigned> owned_place_id_list; //list to stored player properties
    const unsigned short id;
    unsigned short position;
    bool jail_pass;
    bool inJail;
    int money;
    QString user_name;
    unsigned numOfRestaurant;
    //int jailDiceCount[2];
    unsigned jailTurnCounter;
    QMessageBox msgBox;
    bool losed;

public:
    Player(unsigned short, QString);
    Player(const Player&);
    ~Player();
    unsigned short getId() const;
    void addProperty(Property*);
    void removeProperty(Property*);
    vector <unsigned> getOwnedPropertyList() const;
    int getMoney() const;
    bool getJailPass() const;
    QString getName() const;
    bool buyProperty(Property*);
    void changeJailPass();
    unsigned short getPosition() const;
    void setPosition(unsigned);
    Player& operator+=(int);
    Player& operator-=(int);
    bool checkInJail() const;
    void setinJail(bool);
    void setmoney(int);
    void setNumOfRestaurant(unsigned);
    void setJail_pass(bool);
    unsigned getNumOfRestaurant();
    void jailAction(unsigned);
    QString getPlayerInfo() const;
    bool checkLosed() const;
    void setLosed();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
};

#endif // PLAYER_H
