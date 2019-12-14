#include "buildableproperty.h"

BuildableProperty::BuildableProperty(unsigned id, QString name, Color color, unsigned price, unsigned rent):
    Property(id,name, price, rent)
    , propertyColor(color)
{
    levelOfWifiCoverage=0;
    numOfVendingMachines=0;
}

BuildableProperty::BuildableProperty(const BuildableProperty &bp):Property(bp)
                                                                , propertyColor(bp.propertyColor)
                                                                , levelOfWifiCoverage(bp.levelOfWifiCoverage)
                                                                , numOfVendingMachines(bp.numOfVendingMachines)
{

}

Color BuildableProperty::getColor(){
    return propertyColor;
}

unsigned BuildableProperty:: getRentOfProperty(){
    return (Property::getRentOfProperty())+levelOfWifiCoverage*RENTPERLEVELOFWIFICOVERAGE+numOfVendingMachines*RENTOFVENDINGMACHINE;
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

unsigned BuildableProperty::getNumOfVendingMachines(){
    return numOfVendingMachines;
}

void BuildableProperty::resetter(){
    Property::resetter();
    levelOfWifiCoverage=0;
    numOfVendingMachines=0;
}

QString BuildableProperty::getBoxInfo(){
    return (Property::getBoxInfo()
            + "\nBase Rent price(without anything builded): " + QString::number(Property::getRentOfProperty())
            +"\nExtra rent with each of level of wifi coverage: "+QString::number(RENTPERLEVELOFWIFICOVERAGE)
            +"\nExtra rent with vending Machine: " + QString::number(RENTOFVENDINGMACHINE)
            +"\nColor: "+(propertyColor==Red?"Red":(propertyColor==Blue?"Blue":(propertyColor==Yellow?"Yellow":"Green")))
            +"\n"
            +"\nLevel of Wifi Coverage Now: "+QString::number(levelOfWifiCoverage)
            +"\nNumber of Vending Machine Now: "+QString::number(numOfVendingMachines));
}
