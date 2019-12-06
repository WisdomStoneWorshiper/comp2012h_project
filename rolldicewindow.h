#ifndef ROLLDICEWINDOW_H
#define ROLLDICEWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMovie>
#include <QGraphicsScene>
#include <cstdlib>
#include <ctime>

namespace Ui {
class RollDiceWindow;
}

class RollDiceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RollDiceWindow(QWidget *parent = nullptr);
    ~RollDiceWindow();
    void keyPressEvent(QKeyEvent *) override ;
    unsigned getValue();
private:
    Ui::RollDiceWindow *ui;
    QMovie* dice;
    unsigned v;
};

#endif // ROLLDICEWINDOW_H
