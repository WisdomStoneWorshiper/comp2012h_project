#ifndef EMAILMONEY_H
#define EMAILMONEY_H

#include "email.h"

class EmailGetMoney : public Email
{
public:
    EmailGetMoney(int emailOrder);
    void emailAction(Player *p) override; //Increase or decrease player money
    ~EmailGetMoney() ;

private:
    int emailIndex;
};
#endif // EMAILMONEY_H
