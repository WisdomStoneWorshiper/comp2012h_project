#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <list>
#include <QMainWindow>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "gameManager.h"
#include "box.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameManager *gm;
    list<Box> gameField;
    QGraphicsScene *scene;
};
#endif // MAINWINDOW_H
