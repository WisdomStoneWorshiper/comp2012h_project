#ifndef GOTOJAIL_H
#define GOTOJAIL_H

#include "box.h"

class goToJail : public Box{
public:
    goToJail();
    void sendToJail(Player);
};

#endif // GOTOJAIL_H
