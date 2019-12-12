#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gm(new GameManager())
    , scene(new QGraphicsScene())
    , d(new RollDiceWindow(this))
{
    ui->setupUi(this);
    list<Box*> map;
    QFile file(":/map_data/map.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream fin(&file);
    Box* jail;
    while (!fin.atEnd()){
        unsigned id, price, rent;
        QString line, name;
        Box* b;
        QString path;
        fin>>id>>name;
        if (id%7==0 || name=="email"){
            if (id==7){
                b=new Jail(id, name);
            }else b=new Box(id,name);
            path=(":/img/nonProperty/")+(b->getName())+(".png");
        }else if(id==4||id==11||id==17||id==24){
            fin>>price>>rent;
            b=new Restaurant(id,name,price,rent);
            path=(":/img/propertyAsset/")+(b->getName())+("B.png");
        }else{
            Color c;
            fin>>price>>rent;
            if (id<7) c=Yellow;
            else if (id<14) c=Blue;
            else if (id<21) c=Green;
            else c=Red;
            b=new BuildableProperty(id,(name),c,price,rent);
            path=(":/img/propertyAsset/")+(b->getName())+("B.png");
        }
        if ( b->getId()<7){
            b->setRotation(180);
            if (b->getId()==0){
                b->setPos(0,0);
                b->setP1Position(b->x()-130,b->y()-120);
            }else{
                b->setPos((b->getId())*90,0);
                b->setP1Position(map.front()->getP1XPosition()+130+90*(b->getId()-1),map.front()->getP1YPosition());
            }
        }else if (b->getId()<14){
            if (b->getId()==7){
                jail=b;
                b->setPos(540,-130);
                b->setP1Position(map.back()->getP1XPosition()+110,map.back()->getP1YPosition()-50);
                static_cast<Jail*>(jail)->setJailP1Position(jail->getP1XPosition(),jail->getP1YPosition()+40);
            }else if (b->getId()==8){
                b->setRotation(-90);
                b->setPos(540,(b->getId()-7)*90);
                b->setP1Position(map.back()->getP1XPosition(),map.back()->getP1YPosition()+70);
            }else{
                b->setRotation(-90);
                b->setPos(540,(b->getId()-7)*90);
                b->setP1Position(map.back()->getP1XPosition(),map.back()->getP1YPosition()+90);
            }
        }else if (b->getId()<21){
            if (b->getId()==14){
                b->setPos(540,540);
                b->setP1Position(map.back()->getP1XPosition(),map.back()->getP1YPosition()+100);
            }else{
                b->setPos(630-(b->getId()-13)*90,540);
                b->setP1Position(map.back()->getP1XPosition()-90,map.back()->getP1YPosition());
            }
        } else {
            b->setRotation(90);
            if (b->getId()==21){
                b->setPos(0,540);
                b->setP1Position(map.back()->getP1XPosition()-130,map.back()->getP1YPosition());
            }else{
                b->setPos(0,630-(b->getId()-20)*90);
                b->setP1Position(map.back()->getP1XPosition(),map.back()->getP1YPosition()-90);
            }
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
    file.close();
    bool ok=false;
    list<Player*> p_list;
    unsigned numOfPlayer=QInputDialog::getInt(this,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        //gm->init(numOfPlayer);


        for (unsigned i=1;i<=numOfPlayer;++i){

            bool ok=false;
            QString p_name=QInputDialog::getText(this,"",QString("Plaese input player %1 name").arg(QString::number(i)),QLineEdit::Normal,"", &ok);
            if (ok){
                Player* p=new Player(i,p_name);
                p_list.push_back(p);
                QString path;
                path=((":/img/character/character")+QString::number(i)+(".png"));
                p->setPixmap(QPixmap(path));
//                if (i<4)
//                    //p->setPos(map.front()->x()-150+20*i,map.front()->y()-120);
//                    p->setPos(map.front()->getP1XPosition()+20*(i-1),map.front()->getP1YPosition());
//                else
//                    //p->setPos(map.front()->x()-150+20*(i-3),map.front()->y()-70);
//                    p->setPos(map.front()->getP1XPosition()+20*(i-4),map.front()->getP1YPosition()-70);
                gm->playerPositionSetter(p,map.front());
                scene->addItem(p);
            }

        }
    }
//    p_list.front()->setinJail(true);
//    gm->playerPositionSetter(p_list.front(),jail);
    ui->gameArea->setScene(scene);
    ui->gameArea->show();
    //d=new RollDiceWindow(this);
    connect(d,SIGNAL(changevalue(unsigned)),this,SLOT(move(unsigned)));
    gm->init(numOfPlayer,map,p_list);
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

void MainWindow::on_rollDiceBtn_clicked(){

    d->show();
    ui->rollDiceBtn->setEnabled(false);
    //
    //while ()
}

void MainWindow::move (unsigned t){
    qDebug()<<t;
    gm->movePlayer(t);
    if (gm->ableToBuy()) ui->buyBtn->setEnabled(true);
    else if(gm->ableToBuild()) ui->buildBtn->setEnabled(true);
    else if (gm->checkEndTurn()) endTurn();
    ui->endBtn->setEnabled(true);
}

void MainWindow::on_buyBtn_clicked(){
    QMessageBox * comfirmBox=new QMessageBox();
    comfirmBox->setText("You are gonna to buy this asset.");
    comfirmBox->setInformativeText("After purchase, you have $");
    comfirmBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    int choice=comfirmBox->exec();
    if (choice==QMessageBox::Ok){
        gm->buyAsset();
    }
    delete comfirmBox;
    endTurn();
}

void MainWindow::on_buildBtn_clicked(){

}

void MainWindow::on_endBtn_clicked(){
    endTurn();
}

void MainWindow::on_tradeBtn_clicked(){

}

void MainWindow::endTurn(){
    ui->rollDiceBtn->setEnabled(true);
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    gm->moveToNextPlayer();
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
    delete gm;
    delete scene;
}

