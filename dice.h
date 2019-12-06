#ifndef DICE_H
#define DICE_H

#include <QGraphicsPixmapItem>
#include <QTimer>

class Dice : public QGraphicsPixmapItem
{

public:
    Dice();
    Dice(const Dice&);
    ~Dice();
    void rollingDice();
    unsigned stopRolling();
private:
    QTimer* diceTimer;
};

#endif // DICE_H
