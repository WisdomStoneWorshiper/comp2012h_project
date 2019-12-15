#include "tradewindow.h"
#include "ui_tradewindow.h"

//convension constructor
TradeWindow::TradeWindow(const vector<Player *> &playerList, const vector<Box *> &gameField, QWidget *parent) : QDialog(parent),
                                                                                                                ui(new Ui::TradeWindow)
{
    ui->setupUi(this);
    this->playerList = playerList;
    this->gameField = (gameField);
    ui->sellerBox->setEnabled(false);
    ui->propertyBox->setEnabled(false);
    ui->priceField->setEnabled(false);
    valider = nullptr;
    ui->comfirmBtn->setEnabled(false);
}

//destructor
TradeWindow::~TradeWindow()
{
    delete ui;
    if (valider != nullptr)
        delete valider;
    playerList.clear();
    gameField.clear();
}

//initalize the trade window
void TradeWindow::init(Player *buyer)
{
    //clear up the data used by the previous player
    this->buyer = buyer;
    ui->buyerBox->clear();
    ui->sellerBox->clear();
    ui->propertyBox->clear();
    if (valider != nullptr)
        delete valider;
    valider = new QIntValidator(1, buyer->getMoney(), this);
    //add all player to buyer combobox
    for (int target = 0; target < playerList.size(); ++target)
    {
        ui->buyerBox->addItem(playerList[target]->getName());
    }
}

//action will be performed when buyer comboBox is clicked
void TradeWindow::on_buyerBox_activated(const QString &buyerName)
{
    //find the player pointer of the buyer
    buyer = *find_if(playerList.begin(), playerList.end(), [&](const Player *target) { return target->getName().compare(buyerName) == 0; });
    //add rest of the player to the seller
    for (int target = 0; target < playerList.size(); ++target)
    {
        if (playerList[target]->getId() != buyer->getId())
        {
            ui->sellerBox->addItem(playerList[target]->getName());
        }
    }
    ui->sellerBox->setEnabled(true);
}

//action will be performed when seller comboBox is clicked
void TradeWindow::on_sellerBox_activated(const QString &sellerName)
{
     //find the player pointer of the seller
    seller = *find_if(playerList.begin(), playerList.end(), [&](const Player *target) { return target->getName().compare(sellerName) == 0; });
    //find the property owned by the seller and add to property combo box
    for (vector<Box *>::const_iterator box = gameField.begin(); box != gameField.end(); ++box)
    {
        if (typeid(*(*box)) == typeid(BuildableProperty) || typeid(*(*box)) == typeid(Restaurant))
        {
            Property *currentProperty = static_cast<Property *>(*box);
            if (currentProperty->getOwnerId() == (seller)->getId())
            {
                ui->propertyBox->addItem(currentProperty->getName());
            }
        }
    }
    ui->propertyBox->setEnabled(true);
}

//action will be perform when cancel button is clicked
void TradeWindow::on_cancelBtn_clicked()
{
    this->close();
    delete valider;
    valider = nullptr;
}

//action will be performed when property comboBox is clicked
void TradeWindow::on_propertyBox_activated(const QString &targetName)
{
    //find the player pointer of the property going to trade
    vector<Box *>::const_iterator target = find_if(gameField.begin(), gameField.end(), [&](Box *t) { return t->getName().compare(targetName) == 0; });
    targetProperty = static_cast<Property *>(*target);
    ui->priceField->setValidator(valider);
    ui->priceField->setEnabled(true);
}

//action will be performed when value in price field is changed
void TradeWindow::on_priceField_textChanged(const QString &price)
{
    //check whether the buyer have enough money
    if (price.toInt() > buyer->getMoney())
    {
        //if no, do the corresponding action
        ui->priceCheckerMessage->setText("You do not have enough money");
        ui->comfirmBtn->setEnabled(false);
    }
    else
    {
        //if yes, do the corresponding action
        ui->priceCheckerMessage->setText("Please click confirm to finish this trade");
        ui->comfirmBtn->setEnabled(true);
    }
}

//action will be performed when comfirm button is pressed
void TradeWindow::on_comfirmBtn_clicked()
{
    //pass the value to a signel
    doTrade(seller, targetProperty, ui->priceField->text().toUInt());
}
