#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "box.h"

class Jail : public Box
{
public:
    Jail(unsigned, QString);
    Jail(const Jail &);
    double getJailP1XPosition();
    double getJailP1YPosition();
    void setJailP1Position(double, double);

private:
    double jailP1XPosition, jailP1YPosition;
};

#endif // NONPROPERTY_H
