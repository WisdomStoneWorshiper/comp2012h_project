#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <list>

#include "charactor.h"
#include "banker.h"
#include "cardDeck.h"
#include "property.h"
#include "nonProperty.h"

using namespace std;

class GameManager{
public:
    void init();

private:
    list<Charactor> charactorList;

};

#endif // GAMEMANAGER_H
