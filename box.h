#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <queue>

#include "player.h"

using namespace std;

class Box : public QGraphicsPixmapItem {
public:
    Box(QString, unsigned);
    Box(const Box &);
    ~Box();
    virtual void queueUp(Player);
    Player* movePlayer();
    QString getName();
    unsigned getId();

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    unsigned id;
    QString name;
    queue<Player> playerOnThisBox;
};

#endif // BOX_H
