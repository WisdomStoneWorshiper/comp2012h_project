#ifndef EMAILFLY_H
#define EMAILFLY_H

#endif // EMAILFLY_H
#include "email.h"

class EmailMove : public Email{
public:

    EmailMove(int cardOrder);
    void emailAction(Player *p) ;// player position change
    ~EmailMove();
private:
 //    static int cardOrder ;
     int cardIndex;
};
//int EmailFly::cardOrder = 0;
