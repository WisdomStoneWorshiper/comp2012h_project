#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gm(new GameManager())
    , scene(new QGraphicsScene())
    , d(new RollDiceWindow())
{
    ui->setupUi(this);
    vector<Box*> map;
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
                b->setP1Position(map.back()->getP1XPosition(),map.back()->getP1YPosition()+130);
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
    vector<Player*> p_list;
    unsigned numOfPlayer=QInputDialog::getInt(this,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        //gm->init(numOfPlayer);


        for (unsigned i=1;i<=numOfPlayer;++i){

            bool ok=false;
            QString p_name=QInputDialog::getText(this,"",QString("Plaese input player %1 name").arg(QString::number(i)),QLineEdit::Normal,"", &ok);
            if (ok){
                qDebug()<<"c1";
                Player* p=new Player(i,p_name);
                 qDebug()<<"c3";
                p_list.push_back(p);
                 qDebug()<<"c4";
                QString path;
                path=((":/img/character/character")+QString::number(i)+(".png"));
                 qDebug()<<"c5";
                p->setPixmap(QPixmap(path));
                 qDebug()<<"c6";
//                if (i<4)
//                    //p->setPos(map.front()->x()-150+20*i,map.front()->y()-120);
//                    p->setPos(map.front()->getP1XPosition()+20*(i-1),map.front()->getP1YPosition());
//                else
//                    //p->setPos(map.front()->x()-150+20*(i-3),map.front()->y()-70);
//                    p->setPos(map.front()->getP1XPosition()+20*(i-4),map.front()->getP1YPosition()-70);
                 qDebug()<<"c7";
                gm->playerPositionSetter(p_list.back(),map.front());
                 qDebug()<<"c8";
                scene->addItem(p);
            }

        }
    }
//    p_list.front()->setinJail(true);
//    gm->playerPositionSetter(p_list.front(),jail);
    qDebug()<<"w1";
    ui->gameArea->setScene(scene);
    qDebug()<<"w2";
    ui->gameArea->show();
    qDebug()<<"w3";
    //d=new RollDiceWindow(this);
    connect(d,SIGNAL(changevalue(unsigned)),this,SLOT(move(unsigned)));
    qDebug()<<"w4";
    gm->init(numOfPlayer,map,p_list);
    qDebug()<<"w5";
    t=new TradeWindow(p_list,map);
    connect(t,SIGNAL(doTrade(Player* ,Property*,unsigned)),this,SLOT(trade(Player*,Property*,unsigned)));
    m=new MortgageWindow(p_list,map);
    connect(m,SIGNAL(doMortgage(Property*, Mod)),this,SLOT(mortgage(Property*, Mod)));
    qDebug()<<"w6";
    ui->buyBtn->setEnabled(false);
    qDebug()<<"w7";
    ui->endBtn->setEnabled(false);
    qDebug()<<"w8";
    ui->buildBtn->setEnabled(false);
    qDebug()<<"w9";
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

void MainWindow::on_rollDiceBtn_clicked(){
    //d=new RollDiceWindow();
    d->show();
    //move(1);
    ui->rollDiceBtn->setEnabled(false);
    //
    //while ()
}

void MainWindow::move (unsigned t){
    if (gm->getCurrentPlayer()->checkInJail()){
        gm->getCurrentPlayer()->saveJailDice(t);
        if (gm->getCurrentPlayer()->checkInJail()==false){
            gm->movePlayer(0);
        }
        endTurn();
    }else{
    qDebug()<<t;
    gm->movePlayer(t);
    //delete d;
    qDebug()<<"m1";
    ui->endBtn->setEnabled(true);
    qDebug()<<"m2";
    //ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    qDebug()<<"m3";
    if (gm->ableToBuy()){
        qDebug()<<"m5";
        ui->buyBtn->setEnabled(true);
    }else if(gm->ableToIncreaseWifi()||gm->ableToAddVendingMachine()){
        qDebug()<<"m6";
        ui->buildBtn->setEnabled(true);
    }else if (gm->checkEndTurn()){
        qDebug()<<"m7";
        endTurn();
    }
    qDebug()<<"m4";
    }
}

void MainWindow::on_buyBtn_clicked(){
    QMessageBox * comfirmBox=new QMessageBox();
    comfirmBox->setText("You are gonna buy this asset.");
    comfirmBox->setInformativeText("After purchase, you have $"+QString::number(gm->getMoneyAfterBuy()));
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
    QMessageBox * comfirmBox=new QMessageBox();
    //comfirmBox->setText("You are gonna to buy this asset.");
   // comfirmBox->setInformativeText("After purchase, you have $"+QString::number(gm->getMoneyAfterBuy())+" left");
    comfirmBox->setInformativeText("After purchase, you have $"+QString::number(gm->getMoneyAfterBuild())+" left");
    comfirmBox->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    if (gm->ableToAddVendingMachine()){
        comfirmBox->setText("You are gonna add vending machine");
    } else if (gm->ableToIncreaseWifi()){
        comfirmBox->setText("You are gonna increase wifi level");
    }
    int choice=comfirmBox->exec();
    if (choice==QMessageBox::Ok){
        gm->build();
    }
    delete comfirmBox;
    endTurn();
}

void MainWindow::on_endBtn_clicked(){
    endTurn();
}

void MainWindow::on_tradeBtn_clicked(){
//    Tradewindow* tw=new Tradewindow(gm->getCurrentPlayer(),gm->getPlayerList(),gm->getGameField());
//    //connect(tw,SIGNAL(tradeAction(Property*, unsigned)),this,SLOT(trade(Property*, unsigned)));
//    tw->show();
    t->init(gm->getCurrentPlayer());
    t->show();
}

void MainWindow::trade(Player *seller, Property* target, unsigned price){
    gm->tradeAction(seller,target,price);
}

void MainWindow::endTurn(){
    qDebug()<<"e3";
    if (ui->rollDiceBtn->isEnabled()==false)
        ui->rollDiceBtn->setEnabled(true);
    qDebug()<<"e4";
    if (ui->buyBtn->isEnabled())
        ui->buyBtn->setDisabled(true);
    qDebug()<<"e5";
    if (ui->buildBtn->isEnabled())
        ui->endBtn->setDisabled(true);
    qDebug()<<"e6";
    if(ui->endBtn->isEnabled())
        ui->buildBtn->setDisabled(true);
    qDebug()<<"e7";
    qDebug()<<gm->getCurrentPlayer()->getId();
    qDebug()<<"e8"<<gm->getCurrentPlayerInfo();
    gm->moveToNextPlayer();
    qDebug()<<"e1"<<gm->getCurrentPlayerInfo();
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    qDebug()<<"e2";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
    delete gm;
    delete scene;
}


void MainWindow::on_mortgageBtn_clicked()
{
    m->init(gm->getCurrentPlayer());
    m->show();
}

void MainWindow::mortgage(Property* target, Mod mod){

}
