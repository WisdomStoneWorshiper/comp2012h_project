#include "box.h"
#include <QDebug>
Box::Box(unsigned id, QString name) :id(id), name(name){

}

Box::Box(const Box &box){

}

Box::~Box(){

}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setPos(x()+10,y());
    qDebug()<<x()<<" "<<y();
}

//void Box::queueUp(Player target){
//    playerOnThisBox.push(target);
//}

//Player* Box::movePlayer(){
//    Player* target = &playerOnThisBox.front();
//    playerOnThisBox.pop();
//    return target;
//}

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
