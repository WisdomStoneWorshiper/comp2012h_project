#ifndef CHARACTOR_H
#define CHARACTOR_H

//#include <vector>
#include <list>
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
    vector <unsigned> getOwnedPropertyList();

protected:
    vector <unsigned> owned_place_id_list;
    const unsigned short id;
};

#endif // CHARACTOR_H
