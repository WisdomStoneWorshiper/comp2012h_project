#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <QMainWindow>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QFile>
#include <QMessageBox>
#include <QComboBox>

#include "gameManager.h"
#include "box.h"
#include "player.h"
#include "rolldicewindow.h"
#include "restaurant.h"
#include "buildableproperty.h"
#include "jail.h"
#include "tradewindow.h"
#include "mortgagewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void moveCharactor(Player, int);
    void endTurn();
public slots:
     void move(unsigned );
     void trade(Player*,Property*,unsigned);
     void mortgage(Property*, Mod);
     void on_rollDiceBtn_clicked();
     void on_buyBtn_clicked();
     void on_buildBtn_clicked();
     void on_endBtn_clicked();
     void on_tradeBtn_clicked();
private slots:
     void on_mortgageBtn_clicked();

private:
    Ui::MainWindow *ui;
    GameManager *gm;
    vector<Box> gameField;
    QGraphicsScene *scene;
    RollDiceWindow* d;
    TradeWindow* t;
    MortgageWindow* m;
};
#endif // MAINWINDOW_H
