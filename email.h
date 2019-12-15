#ifndef EMAIL_H
#define EMAIL_H
#include "QString"
#include "player.h"

class Email //Abstract Class
{

public:
    Email();
    QString getMessage() const;
    void setMessage(QString);
    virtual void emailAction(Player *p) = 0; //To be overried
    virtual ~Email();

private:
    QString message;
};

#endif // EMAIL_H
