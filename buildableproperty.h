#ifndef BUILDABLEPROPERTY_H
#define BUILDABLEPROPERTY_H

#include <property.h>

enum Color{Red, Blue, Yellow, Green};

class BuildableProperty : public Property
{
public:
    BuildableProperty(unsigned, QString, Color, unsigned, unsigned);
    Color getColor();
    unsigned getRentOfProperty() override;
    unsigned getCostPerLevelOfWifiCoverage();
    unsigned getCostOfVendingMachine();
    void increaseWifiCoverage();
    void addVendingMachines();
private:
    Color propertyColor;
    unsigned levelOfWifiCoverage;
    unsigned numOfVendingMachines;
    const unsigned RENTPERLEVELOFWIFICOVERAGE=200, RENTOFVENDINGMACHINE=300;
    const unsigned COSTPERLEVELOFWIFICOVERAGE=400, COSTOFVENDINGMACHINE=600;
};

#endif // BUILDABLEPROPERTY_H
