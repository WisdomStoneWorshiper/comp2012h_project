#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>

class Box : public QGraphicsPixmapItem {
    public:
    Box();
    Box(const Box &);
};

#endif // BOX_H
