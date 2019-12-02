#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>

class Box : public QGraphicsPixmapItem {
public:
    Box();
    Box(const Box &);
public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:

};

#endif // BOX_H
