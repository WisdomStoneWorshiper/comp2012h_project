#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <property.h>

class Restaurant : public Property
{
public:
    Restaurant(unsigned, QString, unsigned, unsigned);
    unsigned getRentOfProperty(unsigned);
private:
    const unsigned ADDITIONRENTPERRESTAURANT=250;
};

#endif // RESTAURANT_H
