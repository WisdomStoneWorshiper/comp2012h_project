#ifndef CHARACTOR_H
#define CHARACTOR_H

#include <vector>
#include <list>
#include <iterator>
#include <QGraphicsPixmapItem>

#include "property.h"

using namespace std;

class Charactor: public QGraphicsPixmapItem
{
public:
    Charactor();
    void add_property(Property);
    void remove_property(Property);
private:
    list <Property> :: iterator sentinel;
    list <Property> owned_place;
};

#endif // CHARACTOR_H
