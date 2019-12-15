#ifndef NONPROPERTY_H
#define NONPROPERTY_H

#include "box.h"

class Jail : public Box
{
public:
    Jail(const unsigned &, const QString &);
    Jail(const Jail &);
    double getJailP1XPosition();
    double getJailP1YPosition();
    void setJailP1Position(const double &, const double &);

private:
    double jailP1XPosition, jailP1YPosition;
};

#endif // NONPROPERTY_H
