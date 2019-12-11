#include "buildableproperty.h"

BuildableProperty::BuildableProperty(unsigned id, QString name, Color color, unsigned price, unsigned rent):
    Property(id,name, price, rent)
    , propertyColor(color)
{

}

Color BuildableProperty::getColor(){
    return propertyColor;
}

unsigned BuildableProperty:: getRentOfProperty(){
    return Property::getRentOfProperty()+levelOfWifiCoverage*RENTPERLEVELOFWIFICOVERAGE+numOfVendingMachines*RENTOFVENDINGMACHINE;
}

void BuildableProperty:: increaseWifiCoverage(){
    ++levelOfWifiCoverage;
}

void BuildableProperty:: addVendingMachines(){
    ++numOfVendingMachines;
}

unsigned BuildableProperty::getCostPerLevelOfWifiCoverage(){
    return COSTPERLEVELOFWIFICOVERAGE;
}
unsigned BuildableProperty::getCostOfVendingMachine(){
    return COSTOFVENDINGMACHINE;
}

unsigned BuildableProperty::getLevelOfWifiCoverage(){
    return levelOfWifiCoverage;
}
