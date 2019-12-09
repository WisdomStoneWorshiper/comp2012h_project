#include "rolldicewindow.h"
#include "ui_rolldicewindow.h"
#include <QDebug>

RollDiceWindow::RollDiceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RollDiceWindow),
    timer(new QElapsedTimer())
{
    ui->setupUi(this);
    dice=new QMovie(":/img/dice/rollingDice.gif");
    ui->testLabel->setMovie(dice);
    dice->start();
}

RollDiceWindow::~RollDiceWindow()
{
    delete ui;
}

void RollDiceWindow::keyPressEvent(QKeyEvent *e){
    if (e->key()==Qt::Key_Space){
        dice->stop();
        srand (time(NULL));
        unsigned temp=rand() % 6 + 1;
        dice->setFileName((":/img/dice/dice"+QString(temp)+".png"));
        dice->start();
        timer->restart();
        while (timer->elapsed()<2000){
        }
        qDebug()<<timer->elapsed();
        changevalue(temp);
        this->close();
    }
}

unsigned RollDiceWindow::getValue(){
    return v;
}


//void RollDiceWindow::changevalue(unsigned v){
//    this->v=v;
//}
