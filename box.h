#ifndef BOX_H
#define BOX_H

#include <QGraphicsPixmapItem>
#include <QString>
#include <queue>
#include <QMessageBox>

using namespace std;

class Box : public QGraphicsPixmapItem
{
    //Q_OBJECT
public:
    Box();
    Box(const unsigned &, const QString &);
    Box(const Box &);
    virtual ~Box();
    QString getName();
    unsigned getId();
    double getP1XPosition();
    double getP1YPosition();
    void setP1Position(const double &, const double &);
    virtual QString getBoxInfo();

protected slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    unsigned id;
    QString name;
    double p1XPosition, p1YPosition;

protected:
    QMessageBox msgBox;
};

#endif // BOX_H
