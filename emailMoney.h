#ifndef EMAILMONEY_H
#define EMAILMONEY_H

#endif // EMAILMONEY_H
#include "email.h"

class EmailMoney : public Email{
public:
    EmailMoney(int cardOrder);
    void emailAction(Player *p) override;
     ~EmailMoney() override;
private:


    int cardIndex;
};

