#ifndef EMAILDECK_H
#define EMAILDECK_H

#endif // EMAILDECK_H
#include "emailFly.h"
#include "emailJailPass.h"
#include "emailMoney.h"
#include "deque"


//create 4fly 4money 1pass


class EmailDeck{
public:
    EmailDeck();
    void shuffle();
    Email * getEmail();
    bool isEmpty();
private:
    deque<Email*> deck;
    deque<Email*>:: iterator emailOrder;
};
