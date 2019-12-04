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

//Player*& Property::getOwner(){
//    return owner;
//}

//void Property:: changeOwner(Player* newOwner){
//    owner=newOwner;
//}

void Property:: addComputers(unsigned number){
    numOfComputers+=number;
}

void Property:: addVendingMachines(unsigned number){
    numOfVendingMachines+=number;
}
