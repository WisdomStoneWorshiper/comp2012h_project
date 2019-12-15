#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <property.h>

class Restaurant : public Property
{
public:
    Restaurant(const unsigned &, const QString &, const unsigned &, const unsigned &);
    Restaurant(const Restaurant &);
    unsigned getRentOfProperty(const unsigned &);
    QString getBoxInfo() override;

private:
    const unsigned ADDITIONRENTPERRESTAURANT = 250;
};

#endif // RESTAURANT_H
