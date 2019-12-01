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
    if (ok)
        gm->init(numOfPlayer);
   // for (int i=1;i<3;++i){
        Box *b=new Box();
        gameField.push_back(*b);
        QString path= QString::fromStdString(":/img/test1.png");

        b->setPixmap(QPixmap(path));
        b->setPos(-50,-50);
        scene->addItem(b);

        qDebug()<<b->x()<<" "<<b->y();
   // }
    ui->box_0->setScene(scene);
    ui->box_0->show();

}



MainWindow::~MainWindow()
{
    delete ui;
}

