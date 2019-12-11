#ifndef EMAILJAILPASS_H
#define EMAILJAILPASS_H

#endif // EMAILJAILPASS_H
#include "email.h"

class EmailGetJailPass : public Email{ //simple email with one action to player get the Pass
public:
    EmailGetJailPass();
    void emailAction(Player *p) ;
    ~EmailGetJailPass();
};
