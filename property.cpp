#include <property.h>

Property::Property(unsigned id, QString name, unsigned price, unsigned rent):
    Box(id,name)
  , propertyPrice(price)
  , rentOfProperty(rent)
{
    ownerId=0;
}

//Property::Property(const Property &p){

//}

Property::~Property(){

}

unsigned Property::getRentOfProperty(){
    return rentOfProperty;
}

unsigned Property:: getPropertyPrice(){
    return propertyPrice;
}



unsigned Property::getOwnerId(){
    return ownerId;
}

void Property:: changeOwner(unsigned newOwnerId){
    ownerId=newOwnerId;
}
