#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>
#include <QGraphicsItem>


#include "charactor.h"
#include "banker.h"
#include "cardDeck.h"
#include "property.h"
#include "nonProperty.h"
#include "box.h"

using namespace std;

class GameManager{
public:
    void init();

private:
    list<Charactor> charactorList;
    list<Box> gameField;

};

#endif // GAMEMANAGER_H
