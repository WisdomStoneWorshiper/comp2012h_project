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
    delete dice;
    delete timer;

}

void RollDiceWindow::keyPressEvent(QKeyEvent *e){
    if (e->key()==Qt::Key_Space){
        dice->stop();
        timer->restart();
        while (timer->elapsed()<2000){
        }
        unsigned temp=dice->currentFrameNumber()+1;

        this->close();
        dice->start();
        qDebug()<<"r"<<temp;
        changevalue(temp);
    }
}

unsigned RollDiceWindow::getValue(){
    return v;
}

