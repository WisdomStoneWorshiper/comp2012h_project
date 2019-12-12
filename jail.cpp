#include "jail.h"

Jail::Jail(unsigned id, QString name):Box(id,name){

}

Jail::Jail(const Jail & j):Box(j)
                            , jailP1XPosition(j.jailP1XPosition)
                            , jailP1YPosition(j.jailP1YPosition)
{

}

double Jail::getJailP1XPosition(){
    return jailP1XPosition;
}

double Jail::getJailP1YPosition(){
    return jailP1YPosition;
}

void Jail::setJailP1Position(double x, double y){
    jailP1XPosition=x;
    jailP1YPosition=y;
}
