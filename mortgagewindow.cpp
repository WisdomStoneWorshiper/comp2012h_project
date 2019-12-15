#include "mortgagewindow.h"
#include "ui_mortgagewindow.h"

//convension constructor
MortgageWindow::MortgageWindow(const vector<Player *> &playerList, const vector<Box *> &gameField, QWidget *parent) : QDialog(parent),
                                                                                                                      ui(new Ui::MortgageWindow)
{
    ui->setupUi(this);
    this->playerList = playerList;
    this->gameField = gameField;
}

//destructor
MortgageWindow::~MortgageWindow()
{
    delete ui;
    playerList.clear();
    gameField.clear();
}

//initalize the class
void MortgageWindow::init(Player *currentPlayer)
{
    this->currentPlayer = currentPlayer;
    ui->mortgageList->clear();
    ui->mortgageList->setEnabled(false);
    ui->confirmBtn->setEnabled(false);
}

//action will be performed when apply radio button is clicked
void MortgageWindow::on_applyBtn_clicked()
{
    ui->mortgageList->clear();
    ui->payBtn->setChecked(false);
    ui->applyBtn->setChecked(true);
    //find property owned by the user
    for (vector<Box *>::const_iterator box = gameField.begin(); box != gameField.end(); ++box)
    {
        if (typeid(*(*box)) == typeid(BuildableProperty) || typeid(*(*box)) == typeid(Restaurant))
        {
            Property *currentProperty = static_cast<Property *>(*box);
            //if current player own this property, and that property is not in mortgage, add to the combobox
            if (currentProperty->getOwnerId() == currentPlayer->getId() && currentProperty->getMortgage() == false)
            {
                ui->mortgageList->addItem(currentProperty->getName());
            }
        }
    }
    ui->mortgageList->setEnabled(true);
}

//action will be performed when pay radio button is clicked
void MortgageWindow::on_payBtn_clicked()
{
    ui->mortgageList->clear();
    ui->payBtn->setChecked(true);
    ui->applyBtn->setChecked(false);
    for (vector<Box *>::const_iterator box = gameField.begin(); box != gameField.end(); ++box)
    {
        //find property owned by the user
        if (typeid(*(*box)) == typeid(BuildableProperty) || typeid(*(*box)) == typeid(Restaurant))
        {
            Property *currentProperty = static_cast<Property *>(*box);
            //if current player own this property, and that property is in mortgage, add to the combobox
            if (currentProperty->getOwnerId() == currentPlayer->getId() && currentProperty->getMortgage() == true)
            {
                ui->mortgageList->addItem(currentProperty->getName());
            }
        }
    }
    ui->mortgageList->setEnabled(true);
}

//action will be performed when mortgage list comboBox is clicked
void MortgageWindow::on_mortgageList_activated(const QString &targetName)
{
    vector<Box *>::const_iterator target = find_if(gameField.begin(), gameField.end(), [&](Box *t) { return t->getName().compare(targetName) == 0; });
    targetProperty = static_cast<Property *>(*target);
    //if the apply radio button is clicked, so the cooresponding message
    if (ui->applyBtn->isChecked() == true)
    {
        ui->mortgageMessage->setText("After apply, you can get $" + QString::number(targetProperty->getPropertyPrice() / 2));
        ui->confirmBtn->setEnabled(true);
    }
    else if (ui->payBtn->isChecked() == true) //if the apply radio button is clicked, ceck whether current player has enough money to pay the mortgage
    {
        if (currentPlayer->getMoney() < targetProperty->getPropertyPrice() / 2 * 1.1)
        {
            //if no, so the cooresponding message
            ui->mortgageMessage->setText("You need $" + QString::number(targetProperty->getPropertyPrice() / 2 * 1.1) + "\nYou do not have enough money");
        }
        else
        {
            //if yes, so the cooresponding message
            ui->mortgageMessage->setText("You need $" + QString::number(targetProperty->getPropertyPrice() / 2 * 1.1) + "\nYou can return the mortgage");
            ui->confirmBtn->setEnabled(true);
        }
    }
}

//action will be performed when comfirm button is clicked
void MortgageWindow::on_confirmBtn_clicked()
{
    //call the signal depends on which radio button is clicked, then close this window
    if (ui->applyBtn->isChecked() == true)
        doMortgage(targetProperty, Apply);
    else if (ui->payBtn->isChecked() == true)
        doMortgage(targetProperty, Pay);
    this->close();
}

//action will be performed when cancel button is clicked
void MortgageWindow::on_cancelBtn_clicked()
{
    this->close();
}
