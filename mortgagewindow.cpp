#include "mortgagewindow.h"
#include "ui_mortgagewindow.h"

MortgageWindow::MortgageWindow(const vector<Player*> &playerList, const vector<Box *>& gameField,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MortgageWindow)
{
    ui->setupUi(this);
    this->playerList=playerList;
    this->gameField=gameField;
}

MortgageWindow::~MortgageWindow()
{
    delete ui;
    playerList.clear();
    gameField.clear();
}

void MortgageWindow::init(Player* currentPlayer){
    this->currentPlayer=currentPlayer;
    ui->mortgageList->clear();
    ui->mortgageList->setEnabled(false);
    ui->confirmBtn->setEnabled(false);
}

void MortgageWindow::on_applyBtn_clicked()
{
    ui->mortgageList->clear();
    ui->payBtn->setChecked(false);
    ui->applyBtn->setChecked(true);
    for (vector<Box*>::const_iterator box=gameField.begin();box!=gameField.end();++box){
        //qDebug()<<(*box)->getId();
        if (typeid (*(*box))==typeid (BuildableProperty)||typeid (*(*box))==typeid (Restaurant)){
            Property* currentProperty=static_cast<Property*>(*box);
            if (currentProperty->getOwnerId()==currentPlayer->getId() && currentProperty->getMortgage()==false){
                ui->mortgageList->addItem(currentProperty->getName());
            }
        }
    }
    ui->mortgageList->setEnabled(true);
    //ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

void MortgageWindow::on_payBtn_clicked()
{
    ui->mortgageList->clear();
    ui->payBtn->setChecked(true);
    ui->applyBtn->setChecked(false);
    for (vector<Box*>::const_iterator box=gameField.begin();box!=gameField.end();++box){
        //qDebug()<<(*box)->getId();
        if (typeid (*(*box))==typeid (BuildableProperty)||typeid (*(*box))==typeid (Restaurant)){
            Property* currentProperty=static_cast<Property*>(*box);
            if (currentProperty->getOwnerId()==currentPlayer->getId() && currentProperty->getMortgage()==true){
                ui->mortgageList->addItem(currentProperty->getName());
            }
        }
    }
    ui->mortgageList->setEnabled(true);
}

void MortgageWindow::on_mortgageList_activated(const QString &targetName)
{
    vector<Box*>::const_iterator target=find_if(gameField.begin(),gameField.end(), [&]( Box* t){return t->getName().compare(targetName)==0;});
    targetProperty=static_cast<Property*>(*target);
    if (ui->applyBtn->isChecked()==true){
        ui->mortgageMessage->setText("After apply, you can get $"+QString::number(targetProperty->getPropertyPrice()/2));
        ui->confirmBtn->setEnabled(true);
    }else if (ui->payBtn->isChecked()==true){
        if (currentPlayer->getMoney()<targetProperty->getPropertyPrice()/2*1.1){
            ui->mortgageMessage->setText("You need $"+QString::number(targetProperty->getPropertyPrice()/2*1.1)
                                         +"\nYou do not have enough money");
        }else{
            ui->mortgageMessage->setText("You need $"+QString::number(targetProperty->getPropertyPrice()/2*1.1)
                                         +"\nYou can return the mortgage");
            ui->confirmBtn->setEnabled(true);
        }
    }
}

void MortgageWindow::on_confirmBtn_clicked()
{
    if (ui->applyBtn->isChecked()==true)
        doMortgage(targetProperty,Apply);
    else if (ui->payBtn->isChecked()==true)
        doMortgage(targetProperty,Pay);
    this->close();
}

void MortgageWindow::on_cancelBtn_clicked()
{
    this->close();
}
