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
    double getP1XPosition();
    double getP1YPosition();
    void setP1Position(double,double);
//    bool findCurrentBox(Box*);

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    unsigned id;
    QString name;
    double p1XPosition,p1YPosition;
    //queue<Player> playerOnThisBox;
};

#endif // BOX_H
