#include "restaurant.h"

Restaurant::Restaurant(unsigned id, QString name, unsigned price, unsigned rent):
    Property(id,name,price,rent)
{

}

unsigned Restaurant::getRentOfProperty(unsigned numOfExtraRestaurant){
    return Property::getRentOfProperty()+numOfExtraRestaurant*ADDITIONRENTPERRESTAURANT;
}
