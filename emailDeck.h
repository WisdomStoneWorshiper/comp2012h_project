#ifndef EMAILDECK_H
#define EMAILDECK_H

#include "emailMove.h"
#include "emailGetJailPass.h"
#include "emailGetMoney.h"
#include "deque" //double end queue
#include "vector"
#include "list"

using namespace std;

class EmailDeck
{
public:
    EmailDeck();
    //int random_seed (int);
    void shuffle(); //shuffle after reach the last email
    Email *getEmail();
    bool isLastEmail() const;
    ~EmailDeck();

private:
    deque<Email *> deck;
    deque<Email *>::iterator emailToBeGet;
};

#endif // EMAILDECK_H
