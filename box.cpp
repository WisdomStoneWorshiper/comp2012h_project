#include "box.h"

//Box class convension constructor
Box::Box(const unsigned & id, const QString & name) : id(id), name(name)
{
}

//Box class copy constructor
Box::Box(const Box &box) : id(box.id), name(box.name), p1XPosition(box.p1XPosition), p1YPosition(box.p1YPosition)
{
    this->setPos(box.pos());
    this->setRotation(box.rotation());
    this->setPixmap(box.pixmap());
}

//Box class destructor
Box::~Box()
{
}

//when a Box object clicked, display the information of this object
void Box::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    msgBox.setText(this->getBoxInfo());
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);
}

//return the information of this object, it will be overrided by subclass
QString Box::getBoxInfo()
{
    return (name + "\n");
}

//return name of this object
QString Box::getName()
{
    return name;
}

//return id of this object
unsigned Box::getId()
{
    return id;
}

//return x position of where the player 1 should place on this box
double Box::getP1XPosition()
{
    return p1XPosition;
}

//return y position of where the player 1 should place on this box
double Box::getP1YPosition()
{
    return p1YPosition;
}

//set x, y position of where the player 1 should place on this box
void Box::setP1Position(const double& x, const double& y)
{
    p1XPosition = x;
    p1YPosition = y;
}
