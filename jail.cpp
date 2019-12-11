#include "jail.h"

Jail::Jail(unsigned id, QString name):Box(id,name){

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
