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
private:
    deque<Email*> cardDeck;

};
