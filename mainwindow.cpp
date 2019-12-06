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
        list<Box*> map;
        QFile file(":/map_data/map.txt");
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }
        QTextStream fin(&file);

        while (!fin.atEnd()){
            unsigned id, price, rent;
            QString line, name;
            Box* b;
            QString path;
            fin>>id>>name;
            if (id%7==0 || name=="email"){
                b=new Box(id,name);
                path=(":/img/nonProperty/")+(b->getName())+(".png");
            }else{
                Color c;
                fin>>price>>rent;
                if (id<7) c=Yellow;
                else if (id<14) c=Blue;
                else if (id<21) c=Green;
                else c=Red;
                b=new Property(id,(name),c,price,rent);
                path=(":/img/propertyAsset/")+(b->getName())+("B.png");
            }
            if ( b->getId()<7){
                b->setRotation(180);

                if (b->getId()==0) b->setPos(0,0);
                else b->setPos((b->getId())*90,0);
            }else if (b->getId()<14){

                if (b->getId()==7) b->setPos(540,-130);
                else{
                    b->setRotation(-90);
                    b->setPos(540,(b->getId()-7)*90);
                }
            }else if (b->getId()<21){
                if (b->getId()==14) b->setPos(540,540);
                else b->setPos(630-(b->getId()-13)*90,540);
            } else {
                b->setRotation(90);
                if (b->getId()==21) b->setPos(0,540);
                else b->setPos(0,630-(b->getId()-20)*90);
            }
            map.push_back(b);
            b->setPixmap(QPixmap(path));
            scene->addItem(b);

            if (id%7==0 || name=="email"){
                qDebug()<<id<<" "<<(name);
            }else {
                qDebug()<<id<<" "<<(name)<<" "<<price<<" "<<rent;
            }
        }
//                d=new Dice();

//                //d->setPixmap(QPixmap(":/img/dice/dice6.png"));
//                d->setPos(300,400);
        //scene->addItem(d);
        ui->gameArea->setScene(scene);
        ui->gameArea->show();
        file.close();
    }
}

void MainWindow::on_rollDiceBtn_clicked(){
    d=new RollDiceWindow(this);
    d->show();

}

void MainWindow::on_buyBtn_clicked(){

}

void MainWindow::on_buildBtn_clicked(){

}

void MainWindow::on_endBtn_clicked(){

}

void MainWindow::on_tradeBtn_clicked(){

}



MainWindow::~MainWindow()
{
    delete ui;
}

