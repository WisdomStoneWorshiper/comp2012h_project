#include <property.h>
#include <QDebug>

Property::Property(unsigned id, QString name, unsigned price, unsigned rent) : Box(id, name), propertyPrice(price), rentOfProperty(rent)
{
    ownerId = 0;
    mortgage = false;
}

Property::Property(const Property &p) : Box(p), propertyPrice(p.propertyPrice), rentOfProperty(p.rentOfProperty), mortgage(p.mortgage), ownerId(p.ownerId)
{
}

Property::~Property()
{
}

QString Property::getBoxInfo()
{
    return (Box::getBoxInfo() + "\nPrice: " + QString::number(propertyPrice) + "\nMortgage value: " + QString::number(propertyPrice / 2) + "\nIn mortgage?" + (mortgage ? "Yes" : "No") + "\nOwner player Id:" + (ownerId == 0 ? "Banker" : "Player" + QString::number(ownerId)) + "\n");
}

unsigned Property::getRentOfProperty()
{
    return rentOfProperty;
}

unsigned Property::getPropertyPrice()
{
    return propertyPrice;
}

bool Property::getMortgage()
{
    return mortgage;
}

void Property::setMortgage(bool m)
{
    mortgage = m;
}

unsigned Property::getOwnerId()
{
    return ownerId;
}

void Property::changeOwner(unsigned newOwnerId)
{
    ownerId = newOwnerId;
}

void Property::resetter()
{
    mortgage = false;
    ownerId = 0;
}
