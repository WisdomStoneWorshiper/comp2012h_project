#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
#include <vector>

#include "player.h"
#include "banker.h"

#include "restaurant.h"
#include "buildableproperty.h"
#include "jail.h"
#include "box.h"
#include "emailDeck.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTextStream>
#include <QFile>
#include <QInputDialog>


//using namespace std;

class GameManager{

public:
    GameManager();
    ~GameManager();
    QGraphicsScene* & init(QWidget*);
    void moveToNextPlayer();
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
    enum Mod{Apply, Pay};
    void mortgageAction(Property *, int);
    bool checkBankrupt();
    int winner();
    bool haveArrestToSell();
private slots:
    //void on_
    void mortgageAction(unsigned,unsigned);
private:
    QGraphicsScene* gameFieldScene;
    vector<Player*> playerList;
    vector<Box *> gameField;
    unsigned numOfPlayer;
    Player* currentPlayer;
    Banker* banker;
    EmailDeck* deck;
};

#endif // GAMEMANAGER_H
