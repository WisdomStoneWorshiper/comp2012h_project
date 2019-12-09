#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
#include <QGraphicsItem>

#include "player.h"
#include "banker.h"

#include "property.h"
#include "nonProperty.h"
#include "box.h"

using namespace std;

class GameManager{
public:
    GameManager();

    ~GameManager();
    void init(unsigned, list<Box*>, list<Player*>);
    void setCurrentPlayer(Player*);
    void moveToNextPlayer();
    void mavePlayer(unsigned);
    int rollDice();
private slots:
    //void on_
private:
    list<Player*> playerList;
    list<Box*> gameField;
    unsigned numOfPlayer;
    Player* currentPlayer;
};

#endif // GAMEMANAGER_H
