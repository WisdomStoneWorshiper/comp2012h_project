#ifndef EMAILDECK_H
#define EMAILDECK_H

#endif // EMAILDECK_H
#include "emailMove.h"
#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include "deque" //double end queue


//Total create 4Move 7Money 1Pass


class EmailDeck{
public:
    EmailDeck();
    int myrandom(int i); //function for random
    void shuffle();//shuffle before the dequee isCompletelyUsed
    Email * getEmail();
    bool isCompletelyUsed ()const ;  //check if the double end queue go back to the first
    ~EmailDeck();
private:
    deque<Email*> deck;
    deque<Email*>:: iterator emailOrder;
};
