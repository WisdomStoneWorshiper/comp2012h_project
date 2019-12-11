#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
//#include <QPropertyAnimation>
#include <QElapsedTimer>

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
    //bool findCurrentBox(Box*);
    void init(unsigned, list<Box*>, list<Player*>);
    void setCurrentPlayer(Player*);
    void moveToNextPlayer();
    //int rollDice();
    void movePlayer(unsigned);
    void playerPositionSetter(Player*,Box*);
    bool ableToBuy();
    bool ableToBuild();
    bool endTurn();

private slots:
    //void on_
private:
    list<Player*> playerList;
    list<Box*> gameField;
    unsigned numOfPlayer;
    Player* currentPlayer;
    QElapsedTimer* timer;
};

#endif // GAMEMANAGER_H
