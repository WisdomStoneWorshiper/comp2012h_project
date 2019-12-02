#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <queue>

#include "player.h"

using namespace std;

class Box : public QGraphicsPixmapItem {
public:
    Box();
    Box(const Box &);
    ~Box();
    void queueUp(Player);
    QString getName;

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    QString name;
    queue<Player> playerOnThisBox;

};

#endif // BOX_H
