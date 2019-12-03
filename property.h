#ifndef PROPERTY_H
#define PROPERTY_H

#include "box.h"

enum Color{Red, Blue, Yellow, Green};

class Property : public Box{
public:
    Property(Color, unsigned, unsigned);
    ~Property();
    Color getColor();
    unsigned getPropertyPrice();
    unsigned getRentOfProperty();
    Player*& getOwner();
    void changeOwner(Player*);
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
    Player* owner;
};

#endif // PROPERTY_H
