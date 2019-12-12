#include "box.h"
#include <QDebug>
Box::Box(unsigned id, QString name) :id(id), name(name){

}

Box::Box(const Box &box){

}

Box::~Box(){

}

void Box::mousePressEvent(QGraphicsSceneMouseEvent *event){

   // setPos(x()+10,y());
    msgBox.setText(this->getBoxInfo());
   // qDebug()<<this->getBoxInfo();
   // qDebug()<<"I am ready!"<<msgBox.text()<<"done";
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);

  //  QMessageBox * boxContent=new QMessageBox();
   // qDebug()<<this->getName();

   // boxContent->setInformativeText(this->getBoxInfo());
 //   boxContent->setText(this->getBoxInfo());
  //  boxContent->setStandardButtons(QMessageBox::Ok);

  //  boxContent->setDefaultButton(QMessageBox::Ok);

  //  boxContent->exec();
  //  delete boxContent;
 //   qDebug()<<"delete";
  //  int choice=boxContent->exec();

   // if (choice==QMessageBox::Ok){
   //     qDebug()<<"delete";
       // delete boxContent;
  //  }

}
QString Box::getBoxInfo(){
    return (name);
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
