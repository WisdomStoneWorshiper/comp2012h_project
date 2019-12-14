#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    }
    file.close();
    bool ok=false;
    vector<Player*> p_list;
    unsigned numOfPlayer=QInputDialog::getInt(this,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        for (unsigned i=1;i<=numOfPlayer;++i){

            bool ok=false;
            QString p_name=QInputDialog::getText(this,"",QString("Plaese input player %1 name").arg(QString::number(i)),QLineEdit::Normal,"", &ok);
            if (ok){
                Player* p=new Player(i,p_name);
                p_list.push_back(p);
                QString path;
                path=((":/img/character/character")+QString::number(i)+(".png"));
                p->setPixmap(QPixmap(path));
                gm->playerPositionSetter(p_list.back(),map.front());
                scene->addItem(p);
            }

        }
    }
    ui->gameArea->setScene(scene);
    ui->gameArea->show();
    connect(d,SIGNAL(changevalue(unsigned)),this,SLOT(move(unsigned)));
    gm->init(numOfPlayer,map,p_list);
    t=new TradeWindow(p_list,map);
    connect(t,SIGNAL(doTrade(Player* ,Property*,unsigned)),this,SLOT(trade(Player*,Property*,unsigned)));
    m=new MortgageWindow(p_list,map);
    connect(m,SIGNAL(doMortgage(Property*, Mod)),this,SLOT(mortgage(Property*, Mod)));
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

void MainWindow::on_rollDiceBtn_clicked(){
    d->show();
    ui->rollDiceBtn->setEnabled(false);
}

void MainWindow::move (unsigned t){
    ui->endBtn->setEnabled(true);
    if (gm->getCurrentPlayer()->checkInJail()){
        gm->getCurrentPlayer()->saveJailDice(t);
        if (gm->getCurrentPlayer()->checkInJail()==false){
            gm->movePlayer(0);
        }
        endTurn();
    }else{
    gm->movePlayer(t);
//    ui->endBtn->setEnabled(true);
    if (gm->ableToBuy()){
        ui->buyBtn->setEnabled(true);
    }else if(gm->ableToIncreaseWifi()||gm->ableToAddVendingMachine()){
        ui->buildBtn->setEnabled(true);
    }
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
    //the following line maybe crash, if crashed comment it
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
//    if (gm->checkBankrupt()==false)
//        endTurn();
}

void MainWindow::on_buildBtn_clicked(){
    QMessageBox * comfirmBox=new QMessageBox();
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
    //the following line maybe crash, if crashed comment it
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
//    if (gm->checkBankrupt()==false)
//        endTurn();
}

void MainWindow::on_endBtn_clicked(){
    if (gm->checkBankrupt()){
        QMessageBox* checkMsg=new QMessageBox();
        checkMsg->setText("You are going to bankrupt\nAre you sure to end this turn without trying to sell the asset?");
        checkMsg->setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        checkMsg->setDefaultButton(QMessageBox::No);
        int choice=checkMsg->exec();
        //here maybe crash
        //if crashed change whole function to endTurn(); only and comment the rest of the part
        if (choice==QMessageBox::No){
            delete checkMsg;
            return;
        }else{
            delete checkMsg;
            endTurn();
        }
    }else
        endTurn();
}

void MainWindow::on_tradeBtn_clicked(){
    t->init(gm->getCurrentPlayer());
    t->show();
}

void MainWindow::trade(Player *seller, Property* target, unsigned price){
    gm->tradeAction(seller,target,price);
}

void MainWindow::endTurn(){
    if (gm->winner()!=-1){
        QMessageBox* winMsg=new QMessageBox();
        winMsg->setText("Congrat!\nPlayer"+QString::number(gm->winner())+" win the game");
        winMsg->exec();
    }
    if (gm->checkBankrupt()){
        scene->removeItem(gm->getCurrentPlayer());
    }
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


void MainWindow::on_mortgageBtn_clicked()
{
    m->init(gm->getCurrentPlayer());
    m->show();
}

void MainWindow::mortgage(Property* target, Mod mod){
    if (mod==Apply)
        gm->mortgageAction(target,0);
    else
        gm->mortgageAction(target,1);
}
