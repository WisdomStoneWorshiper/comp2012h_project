#ifndef EMAILMONEY_H
#define EMAILMONEY_H

#endif // EMAILMONEY_H
#include "email.h"

class EmailMoney : public Email{
public:
    EmailMoney(int cardOrder);
    void function(Player *p) override;
     ~EmailMoney() override;
private:


    int cardIndex;
};
//int EmailMoney::moneyCardOrder = 0;
