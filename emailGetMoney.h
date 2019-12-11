#ifndef EMAILMONEY_H
#define EMAILMONEY_H

#endif // EMAILMONEY_H
#include "email.h"

class EmailGetMoney : public Email{
public:
    EmailGetMoney(int emailOrder);
    void emailAction(Player *p) override; //Increase or decrease player money
     ~EmailGetMoney() override;
private:

    int emailIndex;
};
