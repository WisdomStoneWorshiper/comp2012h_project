#include "rolldicewindow.h"
#include "ui_rolldicewindow.h"

//convension constructor
RollDiceWindow::RollDiceWindow(QWidget *parent) : QDialog(parent),
                                                  ui(new Ui::RollDiceWindow),
                                                  timer(new QElapsedTimer())
{
    ui->setupUi(this);
    dice = new QMovie(":/img/dice/rollingDice.gif");
    ui->testLabel->setMovie(dice);
    dice->start();
}

//destructor
RollDiceWindow::~RollDiceWindow()
{
    delete ui;
    delete dice;
    delete timer;
}

void RollDiceWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Space) //when space key is pressed, stop rolling the dice
    {
        dice->stop();
        timer->restart();
        //stop for 2 second and then pass the dice face value to a signal
        while (timer->elapsed() < 2000)
        {
        }
        unsigned temp = dice->currentFrameNumber() + 1;
        this->close();
        dice->start();
        changevalue(temp);
    }
}

