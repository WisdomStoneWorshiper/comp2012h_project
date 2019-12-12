#ifndef EMAILMONEY_H
#define EMAILMONEY_H


#include "email.h"

class EmailGetMoney : public Email{
public:
    EmailGetMoney(int emailOrder);
    void emailAction(Player *p) override;
     ~EmailGetMoney() override;
private:

    int emailIndex;
};
#endif // EMAILMONEY_H
