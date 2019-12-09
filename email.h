#ifndef CARD_H
#define CARD_H
#include "QString"
#include "player.h"

class Email{

public:
    Email();
    QString getMessage() const;
    void setMessage(QString);
    virtual void function(Player *p) =0;
    virtual ~ Email() =0;
private:
    QString message;


};

#endif // CARD_H
