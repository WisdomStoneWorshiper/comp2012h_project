#ifndef ROLLDICEWINDOW_H
#define ROLLDICEWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMovie>
#include <QGraphicsScene>
#include <QElapsedTimer>

namespace Ui
{
class RollDiceWindow;
}

class RollDiceWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RollDiceWindow(QWidget *parent = nullptr);
    ~RollDiceWindow() override;
    void keyPressEvent(QKeyEvent *) override;
    unsigned getValue();

signals:
    void changevalue(unsigned);

private:
    Ui::RollDiceWindow *ui;
    QMovie *dice;
    unsigned v;
    QElapsedTimer *timer;
};

#endif // ROLLDICEWINDOW_H
