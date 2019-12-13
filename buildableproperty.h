#ifndef BUILDABLEPROPERTY_H
#define BUILDABLEPROPERTY_H

#include <property.h>

enum Color{Red, Blue, Yellow, Green};

class BuildableProperty : public Property
{
public:
    BuildableProperty(unsigned, QString, Color, unsigned, unsigned);
    BuildableProperty(const BuildableProperty &);
    Color getColor();
    unsigned getRentOfProperty() override;
    unsigned getCostPerLevelOfWifiCoverage();
    unsigned getCostOfVendingMachine();
    unsigned getLevelOfWifiCoverage();
    unsigned getNumOfVendingMachines();
    void increaseWifiCoverage();
    void addVendingMachines();
    QString getBoxInfo() override;
private:
    Color propertyColor;
    unsigned levelOfWifiCoverage;
    unsigned numOfVendingMachines;
    const unsigned RENTPERLEVELOFWIFICOVERAGE=200, RENTOFVENDINGMACHINE=300;
    const unsigned COSTPERLEVELOFWIFICOVERAGE=400, COSTOFVENDINGMACHINE=600;
};

#endif // BUILDABLEPROPERTY_H
