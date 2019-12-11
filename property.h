#ifndef PROPERTY_H
#define PROPERTY_H

#include "box.h"

using namespace std;


//const unsigned RENTPERLEVELOFWIFICOVERAGE=200, RENTOFVENDINGMACHINE=100;
class Property: public Box{
public:
    Property(unsigned, QString, unsigned, unsigned);
    //Property(const Property &);
    ~Property();

    unsigned getPropertyPrice();
    virtual unsigned getRentOfProperty();
    unsigned getOwnerId();

    void changeOwner(unsigned);


private:

    unsigned propertyPrice;
    unsigned rentOfProperty;

    bool mortgage;
    unsigned ownerId;
};

#endif // PROPERTY_H
