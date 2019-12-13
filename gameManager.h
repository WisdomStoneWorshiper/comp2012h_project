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
    bool ableToIncreaseWifi();
    bool ableToAddVendingMachine();
    bool checkEndTurn();
    Player* & getCurrentPlayer();
    void buyAsset();
    void build();
    void emailAction(Box*);
    QString getCurrentPlayerInfo();
   // void inJailAction();
    unsigned getMoneyAfterBuy();
    unsigned getMoneyAfterBuild();
    vector<Player*> getPlayerList() const;
    vector<Box *> getGameField() const;
    void tradeAction(Player*,Property*,unsigned);
private slots:
    //void on_
    void mortgageAction(unsigned,unsigned);
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
