#include "dice.h"

Dice::Dice()
{
    diceTimer.setInterval(16);
    QObject::connect(&diceTimer, &QTimer::timeout, [=](){
        this->rollingDice();
    });
}

Dice::Dice(const Dice& d){

}

void Dice::rollingDice(){
    static unsigned v=0;
    v=++v%6;
    if (v==0){
        this->setPixmap(QPixmap(QString(":/img/dice/dice"+QString(v)+".png")));
    }
}
