#include "box.h"
#include <QDebug>
Box::Box(){

}

Box::Box(const Box &box){

}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setPos(x()-10,y());
    qDebug()<<x()<<" "<<y();
}
