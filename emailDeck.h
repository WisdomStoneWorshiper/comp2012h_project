#ifndef EMAILDECK_H
#define EMAILDECK_H

#include "emailMove.h"
#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include "deque" //double end queue

using namespace std;

//Total create 4Move 7Money 1Pass


class EmailDeck{
public:
    EmailDeck();
    //int random_seed (int);
    void shuffle();//shuffle before the dequee isCompletelyUsed
    Email * getEmail();
    bool isCompletelyUsed ()const ;  //check if the double end queue go back to the first
    ~EmailDeck();
private:
    deque<Email*> deck;
    deque<Email*>:: iterator emailOrder;
};

#endif // EMAILDECK_H
