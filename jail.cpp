#include "jail.h"

//convension constructor of jail class
Jail::Jail(const unsigned & id, const QString & name) : Box(id, name)
{
}

//copy constructor of jail class
Jail::Jail(const Jail &j) : Box(j), jailP1XPosition(j.jailP1XPosition), jailP1YPosition(j.jailP1YPosition)
{
}

//return x position of where the player 1 should place when player 1 is on jail
double Jail::getJailP1XPosition()
{
    return jailP1XPosition;
}

//return y position of where the player 1 should place when player 1 is on jail
double Jail::getJailP1YPosition()
{
    return jailP1YPosition;
}

//set x, y position of where the player 1 should place when player 1 is on jail
void Jail::setJailP1Position(const double & x, const double & y)
{
    jailP1XPosition = x;
    jailP1YPosition = y;
}
