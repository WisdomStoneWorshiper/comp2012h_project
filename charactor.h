#ifndef CHARACTOR_H
#define CHARACTOR_H

#include <vector>
#include <list>
#include <iterator>
#include <QGraphicsPixmapItem>

#include "property.h"

using namespace std;

class Charactor : public QGraphicsPixmapItem
{
public:
    Charactor(unsigned short);
    Charactor(const Charactor&);
    unsigned short getId() const;
    void addProperty(Property*);
    void removeProperty(Property*);
    list <Property*> getOwnedPropertyList();

protected:
    list <Property*> :: iterator sentinel;
    list <Property*> owned_place;
    const unsigned short id;
};

#endif // CHARACTOR_H
