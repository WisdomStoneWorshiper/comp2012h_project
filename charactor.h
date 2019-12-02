#ifndef CHARACTOR_H
#define CHARACTOR_H

#include <vector>
#include <QGraphicsPixmapItem>

class Charactor: public QGraphicsPixmapItem
{
public:
    Charactor();

private:
    unsigned id;
    int momey;
};

#endif // CHARACTOR_H
