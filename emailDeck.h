#ifndef EMAILDECK_H
#define EMAILDECK_H

#endif // EMAILDECK_H
#include "emailMove.h"
#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include "deque" //double end queue


//create 4fly 4money 1pass


class EmailDeck{
public:
    EmailDeck();
    void shuffle();//shuffle before the dequee isCompletelyUsed
    Email * getEmail();
    bool isCompletelyUsed ()const ;  //check if the double end queue go back to the first
    ~EmailDeck();
private:
    deque<Email*> deck;
    deque<Email*>:: iterator emailOrder;
};
