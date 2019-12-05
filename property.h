#ifndef PROPERTY_H
#define PROPERTY_H

#include "box.h"

using namespace std;

enum Color{Red, Blue, Yellow, Green};

class Property: public Box{
public:
    Property();
    Property(unsigned, QString, Color, unsigned, unsigned);
    ~Property();
    Color getColor();
    unsigned getPropertyPrice();
    unsigned getRentOfProperty();
    unsigned getOwnerId();
    void changeOwner(unsigned);
    void addComputers(unsigned);
    void addVendingMachines(unsigned);

private:
    Color propertyColor;
    unsigned numOfComputers;
    unsigned numOfVendingMachines;
    unsigned propertyPrice;
    unsigned rentOfProperty;
    const unsigned addictionRentPerComputer=200, addictionRentPerVendingMachines=100;
    bool mortgage;
    unsigned ownerId;
};

#endif // PROPERTY_H
