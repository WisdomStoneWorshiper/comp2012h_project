#ifndef EMAILJAILPASS_H
#define EMAILJAILPASS_H

#endif // EMAILJAILPASS_H
#include "email.h"

class EmailJailPass : public Email{
public:
    EmailJailPass();
    void emailAction(Player *p) ;
    ~EmailJailPass();
};
