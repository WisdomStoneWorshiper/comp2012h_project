#include <property.h>
#include <QDebug>

//convension constructor
Property::Property(const unsigned & id, const QString & name, const unsigned & price, const unsigned & rent) : Box(id, name), propertyPrice(price), rentOfProperty(rent)
{
    ownerId = 0;
    mortgage = false;
}

//copy construtor
Property::Property(const Property &p) : Box(p), propertyPrice(p.propertyPrice), rentOfProperty(p.rentOfProperty), mortgage(p.mortgage), ownerId(p.ownerId)
{
}

//destructor
Property::~Property()
{
}

//overridded function, return information of property
QString Property::getBoxInfo()
{
    return (Box::getBoxInfo() + "\nPrice: " + QString::number(propertyPrice) + "\nMortgage value: " + QString::number(propertyPrice / 2) + "\nIn mortgage?" + (mortgage ? "Yes" : "No") + "\nOwner player Id:" + (ownerId == 0 ? "Banker" : "Player" + QString::number(ownerId)) + "\n");
}

//return rent of property
unsigned Property::getRentOfProperty()
{
    return rentOfProperty;
}

//return price of this property
unsigned Property::getPropertyPrice()
{
    return propertyPrice;
}

//return whether this property is on mortgage state
bool Property::getMortgage()
{
    return mortgage;
}

//change the state of this property
void Property::setMortgage(const bool & m)
{
    mortgage = m;
}

//return the id of owner
unsigned Property::getOwnerId()
{
    return ownerId;
}

//change the owner of this property
void Property::changeOwner(unsigned newOwnerId)
{
    ownerId = newOwnerId;
}

//reset the the state of this property
void Property::resetter()
{
    mortgage = false;
    ownerId = 0;
}
