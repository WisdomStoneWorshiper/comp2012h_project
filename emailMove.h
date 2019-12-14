#ifndef EMAILFLY_H
#define EMAILFLY_H


#include "email.h"

class EmailMove : public Email{
public:

    EmailMove(int cardOrder);
    void emailAction(Player *p) override;// player position change
    ~EmailMove() override;
private:
     int cardIndex;
};
#endif // EMAILFLY_H
