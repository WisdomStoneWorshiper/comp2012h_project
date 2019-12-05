#include <property.h>

Property::Property(unsigned id, QString name, Color color, unsigned price, unsigned rent):
    Box(id,name)
  , propertyColor(color)
  , propertyPrice(price)
  , rentOfProperty(rent)
{

}

Property::~Property(){

}

Color Property::getColor(){
    return propertyColor;
}

unsigned Property:: getPropertyPrice(){
    return propertyPrice;
}

unsigned Property:: getRentOfProperty(){
    return rentOfProperty+numOfComputers*addictionRentPerComputer+numOfVendingMachines*addictionRentPerVendingMachines;
}

unsigned Property::getOwnerId(){
    return ownerId;
}

void Property:: changeOwner(unsigned newOwnerId){
    ownerId=newOwnerId;
}

void Property:: addComputers(unsigned number){
    numOfComputers+=number;
}

void Property:: addVendingMachines(unsigned number){
    numOfVendingMachines+=number;
}
