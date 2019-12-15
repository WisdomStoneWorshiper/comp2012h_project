#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gm(new GameManager()), d(new RollDiceWindow())
{
    ui->setupUi(this);
    ui->gameArea->setScene(gm->init(this));
    ui->gameArea->show();
    connect(d, SIGNAL(changevalue(unsigned)), this, SLOT(move(unsigned)));
    t = new TradeWindow(gm->getPlayerList(), gm->getGameField());
    connect(t, SIGNAL(doTrade(Player *, Property *, unsigned)), this, SLOT(trade(Player *, Property *, unsigned)));
    m = new MortgageWindow(gm->getPlayerList(), gm->getGameField());
    connect(m, SIGNAL(doMortgage(Property *, Mod)), this, SLOT(mortgage(Property *, Mod)));
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d;
    delete gm;
    delete t;
    delete m;
}

void MainWindow::on_rollDiceBtn_clicked()
{
    d->show();
    ui->rollDiceBtn->setEnabled(false);
}

void MainWindow::move(unsigned t)
{
    ui->endBtn->setEnabled(true);
    if (gm->getCurrentPlayer()->checkInJail())
    {
        gm->getCurrentPlayer()->jailAction(t);
        if (gm->getCurrentPlayer()->checkInJail() == false)
        {
            gm->movePlayer(0);
        }
        endTurn();
    }
    else
    {
        gm->movePlayer(t);
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

void MainWindow::on_buyBtn_clicked()
{
    QMessageBox *comfirmBox = new QMessageBox();
    comfirmBox->setText("You are gonna buy this asset.");
    comfirmBox->setInformativeText("After purchase, you have $" + QString::number(gm->getMoneyAfterBuy()));
    comfirmBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    int choice = comfirmBox->exec();
    if (choice == QMessageBox::Ok)
    {
        gm->buyAsset();
    }
    //the following line maybe crash, if crashed comment it
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
    //    if (gm->checkBankrupt()==false)
    //        endTurn();
    ui->buyBtn->setEnabled(false); //by tat
}

void MainWindow::on_buildBtn_clicked()
{
    if (!gm->ableToIncreaseWifi() && !gm->ableToAddVendingMachine())
        return;
    QMessageBox *comfirmBox = new QMessageBox();
    comfirmBox->setInformativeText("After purchase, you have $" + QString::number(gm->getMoneyAfterBuild()) + " left");
    comfirmBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    comfirmBox->setDefaultButton(QMessageBox::Ok);
    if (gm->ableToAddVendingMachine())
    {
        comfirmBox->setText("You are gonna add vending machine");
    }
    else if (gm->ableToIncreaseWifi())
    {
        comfirmBox->setText("You are gonna increase wifi level");
    }
    int choice = comfirmBox->exec();
    if (choice == QMessageBox::Ok)
    {
        gm->build();
    }
    //the following line maybe crash, if crashed comment it
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
    delete comfirmBox;
    //    if (gm->checkBankrupt()==false)
    //        endTurn();

    ui->buildBtn->setEnabled(false); //by tat
}

void MainWindow::on_endBtn_clicked()
{
    if (gm->checkBankrupt())
    {
        QMessageBox *checkMsg = new QMessageBox();
        checkMsg->setText("You are going to bankrupt\nAre you sure to end this turn without trying to sell the asset?");
        checkMsg->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
        checkMsg->setDefaultButton(QMessageBox::No);
        int choice = checkMsg->exec();
        //here maybe crash
        //if crashed change whole function to endTurn(); only and comment the rest of the part
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

void MainWindow::on_tradeBtn_clicked()
{
    t->init(gm->getCurrentPlayer());
    t->show();
}

void MainWindow::trade(Player *seller, Property *target, unsigned price)
{
    gm->tradeAction(seller, target, price);
}

void MainWindow::endTurn()
{
    if (gm->winner() != -1)
    {
        QMessageBox *winMsg = new QMessageBox();
        winMsg->setText("Congrat!\nPlayer" + QString::number(gm->winner()) + " win the game");
        QPushButton *endGame = winMsg->addButton("End Game", QMessageBox::ActionRole);
        QPushButton *playAgain = winMsg->addButton("Play Again", QMessageBox::ActionRole);
        winMsg->exec();
        if (winMsg->clickedButton() == endGame)
        {
            delete winMsg;
            exit(0);
        }
        else if (winMsg->clickedButton() == playAgain)
        {
            delete winMsg;
            ui->gameArea->setScene(gm->init(this));
        }
    }
    ui->rollDiceBtn->setEnabled(true);
    ui->buyBtn->setEnabled(false);
    ui->endBtn->setEnabled(false);
    ui->buildBtn->setEnabled(false);
    gm->moveToNextPlayer();
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}

void MainWindow::on_mortgageBtn_clicked()
{
    m->init(gm->getCurrentPlayer());
    m->show();
}

void MainWindow::mortgage(Property *target, Mod mod)
{
    if (mod == Apply)
        gm->mortgageAction(target, 0);
    else
        gm->mortgageAction(target, 1);
    ui->playerInfoTag->setText(gm->getCurrentPlayerInfo());
}
