#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
#include <QGraphicsItem>


#include "player.h"
#include "banker.h"
#include "cardDeck.h"
#include "property.h"
#include "nonProperty.h"
#include "box.h"

using namespace std;

class GameManager{
public:
    GameManager();
    ~GameManager();
    void init(int, list<Box>, list<Player>);

private:
    list<Player> playerList;
    list<Box> gameField;
    int numOfPlayer;
};

#endif // GAMEMANAGER_H
