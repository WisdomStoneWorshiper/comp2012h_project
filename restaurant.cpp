#include "restaurant.h"

//constructor
Restaurant::Restaurant(const unsigned & id, const QString & name, const unsigned & price, const unsigned & rent) : Property(id, name, price, rent)
{
}

//destructor
Restaurant::Restaurant(const Restaurant &r) : Property(r)
{
}

//return rent of this restaurant
unsigned Restaurant::getRentOfProperty(const unsigned & numOfExtraRestaurant)
{
    return Property::getRentOfProperty() + numOfExtraRestaurant * ADDITIONRENTPERRESTAURANT;
}

//overridded function, return information of this restaurant
QString Restaurant::getBoxInfo()
{
    return (Property::getBoxInfo() + "\nBasic rent price: " + QString::number(Property::getRentOfProperty()) + "\nExtra rent of owner own each of extra restauant: " + QString::number(ADDITIONRENTPERRESTAURANT));
}
