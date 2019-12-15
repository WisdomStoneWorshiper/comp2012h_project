#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QCloseEvent>

#include "gameManager.h"
#include "property.h"
#include "player.h"
#include "rolldicewindow.h"
#include "tradewindow.h"
#include "mortgagewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void moveCharactor(const Player &, const int &);
    void endTurn();
    void closeEvent (QCloseEvent *);
public slots:
    void move(const unsigned &);
    void trade(Player *, Property *, const unsigned &);
    void mortgage(Property *, const Mod &);
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
    RollDiceWindow *d;
    TradeWindow *t;
    MortgageWindow *m;
};
#endif // MAINWINDOW_H
