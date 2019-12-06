#include "dice.h"

Dice::Dice()
{
//    diceTimer=new QTimer();
//    diceTimer->setInterval(16);
//    QObject::connect(&*diceTimer, &QTimer::timeout, [=](){
        this->rollingDice();
    //});
}

Dice::Dice(const Dice& d){

}

Dice::~Dice(){

}

void Dice::rollingDice(){
    static unsigned v=0;
    v=++v%6;
    if (v==0){
        this->setPixmap(QPixmap(QString(":/img/dice/dice"+QString(6)+".png")));
    }else {
        this->setPixmap(QPixmap(QString(":/img/dice/dice"+QString(v)+".png")));
    }

}

unsigned Dice::stopRolling(){

}
