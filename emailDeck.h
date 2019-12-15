#ifndef EMAILDECK_H
#define EMAILDECK_H

#include "emailMove.h"
#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include "deque" //double end queue


using namespace std;

class EmailDeck
{
public:
    EmailDeck(); //Total create 5Move 7Money 1Pass email for user to draw
    void shuffle(); //shuffle after reach the last email
    Email *getEmail();
    bool isLastEmail() const;
    ~EmailDeck();

private:
    deque<Email *> deck;
    deque<Email *>::iterator emailToBeGet;
};

#endif // EMAILDECK_H
