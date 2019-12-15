#include "mainwindow.h"
#include "ui_mainwindow.h"

//convension constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gm(new GameManager()), d(new RollDiceWindow())
{
    ui->setupUi(this);
    ui->gameArea->setScene(gm->init(this)); //call game manager initalize the game
    ui->gameArea->show();
    connect(d, SIGNAL(changevalue(unsigned)), this, SLOT(move(unsigned))); //connect a signal from RollDiceWindow class to a slot in this class
    t = new TradeWindow(gm->getPlayerList(), gm->getGameField()); //new a TradeWindow class
    connect(t, SIGNAL(doTrade(Player *, Property *, unsigned)), this, SLOT(trade(Player *, Property *, unsigned))); //connect a signal from TradeWindow class to a slot in this class
    m = new MortgageWindow(gm->getPlayerList(), gm->getGameField()); //new a Mortgage class
    connect(m, SIGNAL(doMortgage(Property *, Mod)), this, SLOT(mortgage(Property *, Mod))); //connect a signal from MortgageWindow class to a slot in this class
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

//destructor
MainWindow::~MainWindow()
{
    delete ui;
    delete d;
    delete gm;
    delete t;
    delete m;
}

//action will be performed when roll dice button is clicked
void MainWindow::on_rollDiceBtn_clicked()
{
    d->show();
    ui->rollDiceBtn->setEnabled(false);
}

//based on the value from the signal from RollDiceWindow, do the cooresponding act
void MainWindow::move(const unsigned & diceValue)
{
    ui->endBtn->setEnabled(true);
    if (gm->getCurrentPlayer()->checkInJail())
    {
        gm->getCurrentPlayer()->jailAction(diceValue);
        if (gm->getCurrentPlayer()->checkInJail() == false)
        {
            gm->movePlayer(0);
        }
        endTurn();
    }
    else
    {
        gm->movePlayer(diceValue);
        if (gm->ableToBuy())
        {
            ui->buyBtn->setEnabled(true);
        }
        else if (gm->ableToIncreaseWifi() || gm->ableToAddVendingMachine())
        {
            ui->buildBtn->setEnabled(true);
        }
    }
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

//action will be performed when buy button is clicked
void MainWindow::on_buyBtn_clicked()
{
    QMessageBox *comfirmBox = new QMessageBox();
    //ask user to comfirm their act
    comfirmBox->setText("You are gonna buy this asset.");
    comfirmBox->setInformativeText("After purchase, you have $" + QString::number(gm->getMoneyAfterBuy()));
    comfirmBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    int choice = comfirmBox->exec();
    if (choice == QMessageBox::Ok)
    {
        gm->buyAsset();
    }
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
    ui->buyBtn->setEnabled(false);
}

//action will be performed when build button is clicked
void MainWindow::on_buildBtn_clicked()
{
    if (!gm->ableToIncreaseWifi() && !gm->ableToAddVendingMachine())
        return;
    //ask user to comfirm their act
    QMessageBox *comfirmBox = new QMessageBox();
    comfirmBox->setInformativeText("After purchase, you have $" + QString::number(gm->getMoneyAfterBuild()) + " left");
    comfirmBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    //if they can add a vending machine, show the corresponding message
    if (gm->ableToAddVendingMachine())
    {
        comfirmBox->setText("You are gonna add vending machine");
    }
    else if (gm->ableToIncreaseWifi()) //if they cannot add a vending machine but can increase wifi coverage, show the corresponding message
    {
        comfirmBox->setText("You are gonna increase wifi level");
    }
    int choice = comfirmBox->exec();
    if (choice == QMessageBox::Ok)
    {
        gm->build();
    }
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
    ui->buildBtn->setEnabled(false);
}

//action will be performed when end button is clicked
void MainWindow::on_endBtn_clicked()
{
    //if the current player is going to bankrupt, ask him/her whether him/her comfirm to end this turn
    if (gm->checkBankrupt())
    {
        QMessageBox *checkMsg = new QMessageBox();
        checkMsg->setText("You are going to bankrupt\nAre you sure to end this turn without trying to sell the asset?");
        checkMsg->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        checkMsg->setDefaultButton(QMessageBox::No);
        int choice = checkMsg->exec();
        if (choice == QMessageBox::No)
        {
            delete checkMsg;
            return;
        }
        else
        {
            delete checkMsg;
            endTurn();
        }
    }
    else
        endTurn();
}

//action will be performed when trade button is clicked
void MainWindow::on_tradeBtn_clicked()
{
    t->init(gm->getCurrentPlayer());
    t->show();
}

//slot connect to a signal at TradeWindow class, it will pass the value from TradeWindow to game manager
void MainWindow::trade(Player *seller, Property *target, const unsigned & price)
{
    gm->tradeAction(seller, target, price);
}

//turn end action
void MainWindow::endTurn()
{
    //check whether there are winner
    if (gm->winner() != -1)
    {
        //show the congrat message
        QMessageBox *winMsg = new QMessageBox();
        winMsg->setText("Congrat!\nPlayer" + QString::number(gm->winner()) + " win the game");
        QPushButton *endGame = winMsg->addButton("End Game", QMessageBox::ActionRole);
        QPushButton *playAgain = winMsg->addButton("Play Again", QMessageBox::ActionRole);
        winMsg->exec();
        //if player no longer want to play, end program, if player still want to player, call game manager to initalize the game
        if (winMsg->clickedButton() == endGame)
        {
            delete winMsg;
            exit(0);
        }
        else if (winMsg->clickedButton() == playAgain)
        {
            ui->gameArea->setScene(gm->init(this));
            delete winMsg;
            return;
        }
    }
    ui->rollDiceBtn->setEnabled(true);
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    gm->moveToNextPlayer();
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

//action will be performed when mortgage button is clicked
void MainWindow::on_mortgageBtn_clicked()
{
    m->init(gm->getCurrentPlayer());
    m->show();
}

//slot connect to a signal at Mortgage class, it will pass the value from Mortgage to game manager
void MainWindow::mortgage(Property *target, const Mod & mod)
{
    if (mod == Apply)
        gm->mortgageAction(target, 0);
    else
        gm->mortgageAction(target, 1);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

//action will be performed when closing cross is clicked
void MainWindow::closeEvent (QCloseEvent *event){
    QMessageBox::StandardButton closeBtn = QMessageBox::question( this, "You are about to leave the game",
                                                                    tr("Are you sure?\n"),
                                                                    QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (closeBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
        }
}
