#include "rolldicewindow.h"
#include "ui_rolldicewindow.h"

RollDiceWindow::RollDiceWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RollDiceWindow)
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
        v=rand() % 6 + 1;
        dice->setFileName((":/img/dice/dice"+QString(v)+".png"));
        dice->start();
    }
}

unsigned RollDiceWindow::getValue(){
    return v;
}
