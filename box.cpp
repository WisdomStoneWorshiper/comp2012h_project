#include "box.h"

Box::Box(unsigned id, QString name) :id(id), name(name){

}

Box::Box(const Box &box):id(box.id)
                        , name(box.name)
                        , p1XPosition(box.p1XPosition)
                        , p1YPosition(box.p1YPosition)
{
    this->setPos(box.pos());
    this->setRotation(box.rotation());
    this->setPixmap(box.pixmap());
}

Box::~Box(){

}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event){
    msgBox.setText(this->getBoxInfo());
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);
}
QString Box::getBoxInfo(){
    return (name+"\n");
}

QString Box::getName(){
    return name;
}

unsigned Box::getId(){
    return id;
}

double Box::getP1XPosition(){
    return p1XPosition;
}

double Box::getP1YPosition(){
    return p1YPosition;
}

void Box::setP1Position(double x, double y){
    p1XPosition=x;
    p1YPosition=y;
}
