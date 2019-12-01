#ifndef CHARACTOR_H
#define CHARACTOR_H

#include <vector>
#include <QGraphicsRectItem>

class Charactor: public QGraphicsRectItem
{
public:
    Charactor();

private:
    unsigned id;
    int momey;
};

#endif // CHARACTOR_H
