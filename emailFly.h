#ifndef EMAILFLY_H
#define EMAILFLY_H

#endif // EMAILFLY_H
#include "email.h"

class EmailFly : public Email{
public:

    EmailFly(int cardOrder);
    void emailAction(Player *p) ;// player position change
    ~EmailFly();
private:
 //    static int cardOrder ;
     int cardIndex;
};
//int EmailFly::cardOrder = 0;
