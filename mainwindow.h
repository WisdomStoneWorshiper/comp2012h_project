#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <QMainWindow>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include <QFile>
#include <QMessageBox>

#include "gameManager.h"
#include "box.h"
#include "player.h"
#include "rolldicewindow.h"
#include "restaurant.h"
#include "buildableproperty.h"

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
     void on_rollDiceBtn_clicked();
     void on_buyBtn_clicked();
     void on_buildBtn_clicked();
     void on_endBtn_clicked();
     void on_tradeBtn_clicked();
private:
    Ui::MainWindow *ui;
    GameManager *gm;
    list<Box> gameField;
    QGraphicsScene *scene;
    RollDiceWindow* d;
};
#endif // MAINWINDOW_H
