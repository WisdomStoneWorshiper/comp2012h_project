#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gm(new GameManager)
    , scene(new QGraphicsScene())
{
    ui->setupUi(this);
    bool ok=false;
    int numOfPlayer=QInputDialog::getInt(this,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        //gm->init(numOfPlayer);
    }
   // for (int i=1;i<3;++i){
        Box *b=new Box(0, "startpoint");
        gameField.push_back(*b);
        QString path= (":/img/nonProperty/")+(b->getName())+(".png");

        b->setPixmap(QPixmap(path));

        scene->addItem(b);

        qDebug()<<b->x()<<" "<<b->y();
   // }
    ui->gameArea->setScene(scene);
    ui->gameArea->show();
    b->setPos(0,0);
}



MainWindow::~MainWindow()
{
    delete ui;
}

