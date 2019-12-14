#ifndef EMAIL_H
#define EMAIL_H
#include "QString"
#include "player.h"

class Email{

public:
    Email();
    QString getMessage() const;
    void setMessage(QString);
    virtual void emailAction(Player *p) =0;
    virtual ~Email();
private:
    QString message;
};

#endif // EMAIL_H
