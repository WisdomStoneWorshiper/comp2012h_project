#ifndef EMAILJAILPASS_H
#define EMAILJAILPASS_H

#include "email.h"

class EmailGetJailPass : public Email
{ //simple email with one action to player get the Pass
public:
    EmailGetJailPass();
    void emailAction(Player *p) override; // get a jail pass if player dont have one
    ~EmailGetJailPass() override;
};
#endif // EMAILJAILPASS_H
