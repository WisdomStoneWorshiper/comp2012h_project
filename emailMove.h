#ifndef EMAILFLY_H
#define EMAILFLY_H


#include "email.h"
#
class EmailMove : public Email{
public:

    EmailMove(int cardOrder);
    void emailAction(Player *p) override;// player position change
    ~EmailMove() override;
private:
 //    static int cardOrder ;
     int cardIndex;
};
//int EmailFly::cardOrder = 0;
#endif // EMAILFLY_H
