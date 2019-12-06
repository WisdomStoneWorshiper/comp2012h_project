#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <queue>


using namespace std;

class Box : public QGraphicsPixmapItem {
public:
    Box();
    Box(unsigned, QString);
    Box(const Box &);
    ~Box();
//    virtual void queueUp(Player);
//    Player* movePlayer();
    QString getName();
    unsigned getId();

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    unsigned id;
    QString name;
    //queue<Player> playerOnThisBox;
};

#endif // BOX_H
