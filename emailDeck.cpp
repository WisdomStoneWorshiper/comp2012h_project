#include "emailDeck.h"

EmailDeck::EmailDeck()
{ //Total create 5Move 7Money 1Pass email for user to draw
    for (int i = 1; i <= 5; ++i)
    {
        EmailMove *p = new EmailMove(i);
        deck.push_back(p);
    }

    for (int i = 1; i <= 7; ++i)
    {
        EmailGetMoney *p = new EmailGetMoney(i); // create Email with a emailOrder parameter
        deck.push_back(p);
    }

    deck.push_back(new EmailGetJailPass);
    emailToBeGet = deck.begin();
}
EmailDeck::~EmailDeck()
{ //delete each Email pointer

    for (unsigned i = 0; deck[i] != deck.back(); ++i)
        delete deck[i];
    delete deck.back();
    deck.clear();
}

void EmailDeck::shuffle()
{ //shuffle after reach the last email

    std::random_shuffle(deck.begin(), deck.end());
    emailToBeGet = deck.begin();
}

bool EmailDeck::isLastEmail() const
{
    return (emailToBeGet == deck.end());
}

Email *EmailDeck ::getEmail()
{

    deque<Email *>::iterator temp;
    temp = emailToBeGet;
    ++emailToBeGet;
    return *temp;
}
