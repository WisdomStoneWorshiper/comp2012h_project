#include "restaurant.h"

Restaurant::Restaurant(unsigned id, QString name, unsigned price, unsigned rent) : Property(id, name, price, rent)
{
}

Restaurant::Restaurant(const Restaurant &r) : Property(r)
{
}

unsigned Restaurant::getRentOfProperty(unsigned numOfExtraRestaurant)
{
    return Property::getRentOfProperty() + numOfExtraRestaurant * ADDITIONRENTPERRESTAURANT;
}

QString Restaurant::getBoxInfo()
{
    return (Property::getBoxInfo() + "\nBasic rent price: " + QString::number(Property::getRentOfProperty()) + "\nExtra rent of owner own each of extra restauant: " + QString::number(ADDITIONRENTPERRESTAURANT));
}
