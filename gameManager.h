#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
#include <vector>
//#include <QPropertyAnimation>
#include <QElapsedTimer>

#include "player.h"
#include "banker.h"

#include "restaurant.h"
#include "buildableproperty.h"
#include "jail.h"
#include "box.h"
#include "emailDeck.h"
#include "emailMove.h"
//#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include <QMessageBox>


//using namespace std;

class GameManager{
public:
    GameManager();
    ~GameManager();
    //bool findCurrentBox(Box*);
    void init(unsigned, vector<Box*>, vector<Player*>);
    //void setCurrentPlayer(Player*);
    void moveToNextPlayer();
    //int rollDice();
    void movePlayer(unsigned);
    void playerPositionSetter(Player*,Box*);
    bool ableToBuy();
    bool ableToBuild();
    bool checkEndTurn();
    Player* & getCurrentPlayer();
    void buyAsset();
    void emailAction(Box*);
    QString getCurrentPlayerInfo();
    void inJailAction();
private slots:
    //void on_
private:
    vector<Player*> playerList;
    vector<Box *> gameField;
    unsigned numOfPlayer;
    Player* currentPlayer;
    Banker* banker;
    QElapsedTimer* timer;
    EmailDeck* deck;
};

#endif // GAMEMANAGER_H
