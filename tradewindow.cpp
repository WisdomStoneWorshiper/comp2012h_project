#include "tradewindow.h"
#include "ui_tradewindow.h"
#include <QDebug>

TradeWindow::TradeWindow(const vector<Player*> &playerList, const vector<Box *>& gameField, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TradeWindow)
{
    ui->setupUi(this);
    qDebug()<<"w9";
        this->playerList=playerList;
    qDebug()<<"w10";
        this->gameField=(gameField);
    qDebug()<<"w11";
    ui->propertyBox->setEnabled(false);
    qDebug()<<"w12";
    ui->priceField->setEnabled(false);
    qDebug()<<"w13";
    valider=nullptr;
    //ui->priceField->setInputMask("99999");
    qDebug()<<"w14";
    //ui->cancelBtn->setEnabled(false);
    ui->comfirmBtn->setEnabled(false);
}

TradeWindow::~TradeWindow()
{
    delete ui;
    if (valider!=nullptr)
        delete valider;
}

void TradeWindow::init(Player* buyer){
    this->buyer=buyer;
    qDebug()<<"tw1"<<buyer->getId();
    if (valider!=nullptr)
        delete valider;
    valider=new QIntValidator(1,buyer->getMoney(),this);
    for (int target=0;target<playerList.size();++target){
        if (playerList[target]->getId()!=buyer->getId()){
            ui->sellerBox->addItem(playerList[target]->getName());
        }
    }
    ui->sellerBox->clear();
    ui->propertyBox->clear();
}

void TradeWindow::on_sellerBox_activated(const QString &sellerName)
{

    ui->propertyBox->setEnabled(true);
    qDebug()<<sellerName;
    seller=*find_if(playerList.begin(),playerList.end(), [&](const Player* target){return target->getName().compare(sellerName)==0;});

    for (vector<Box*>::const_iterator box=gameField.begin();box!=gameField.end();++box){
        qDebug()<<(*box)->getId();
        if (typeid (*(*box))==typeid (BuildableProperty)||typeid (*(*box))==typeid (Restaurant)){
            Property* currentProperty=static_cast<Property*>(*box);
            if (currentProperty->getOwnerId()==(seller)->getId()){
                ui->propertyBox->addItem(currentProperty->getName());
            }
        }
    }

}

void TradeWindow::on_cancelBtn_clicked()
{
    this->close();
    delete valider;
    valider=nullptr;
}

void TradeWindow::on_propertyBox_activated(const QString &targetName)
{
    vector<Box*>::const_iterator target=find_if(gameField.begin(),gameField.end(), [&]( Box* t){return t->getName().compare(targetName)==0;});
    targetProperty=static_cast<Property*>(*target);
    ui->priceField->setValidator(valider);
    ui->priceField->setEnabled(true);
}

void TradeWindow::on_priceField_textChanged(const QString &price)
{
    if (price.toInt()>buyer->getMoney()){
        ui->priceCheckerMessage->setText("You do not have enough money");
        ui->comfirmBtn->setEnabled(false);
    }else{
        ui->priceCheckerMessage->setText("Please click confirm to finish this trade");
        ui->comfirmBtn->setEnabled(true);
    }
}

void TradeWindow::on_comfirmBtn_clicked()
{
    doTrade(seller,targetProperty,ui->priceField->text().toUInt());
}
