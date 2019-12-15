#ifndef PROPERTY_H
#define PROPERTY_H

#include "box.h"
#include <QPushButton>

using namespace std;

class Property : public Box
{

public:
    Property(const unsigned &, const QString &, const unsigned &, const unsigned &);
    Property(const Property &);
    ~Property();
    QString getBoxInfo() override;
    unsigned getPropertyPrice();
    virtual unsigned getRentOfProperty();
    unsigned getOwnerId();
    bool getMortgage();
    void setMortgage(const bool &);
    void changeOwner(unsigned);
    virtual void resetter();

private:
    unsigned propertyPrice;
    unsigned rentOfProperty;
    bool mortgage;
    unsigned ownerId;
};

#endif // PROPERTY_H
