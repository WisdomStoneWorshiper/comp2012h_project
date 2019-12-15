#include "buildableproperty.h"

//convension constructor
BuildableProperty::BuildableProperty(const unsigned & id, const QString & name, const Color & color,  const unsigned & price, const unsigned & rent) : Property(id, name, price, rent), propertyColor(color)
{
    levelOfWifiCoverage = 0;
    numOfVendingMachines = 0;
}

//copy constructor
BuildableProperty::BuildableProperty(const BuildableProperty &bp) : Property(bp), propertyColor(bp.propertyColor), levelOfWifiCoverage(bp.levelOfWifiCoverage), numOfVendingMachines(bp.numOfVendingMachines)
{
}

//return color of this buildable Property
Color BuildableProperty::getColor()
{
    return propertyColor;
}

//return rent of this buildable Property
unsigned BuildableProperty::getRentOfProperty()
{
    return Property::getRentOfProperty() + levelOfWifiCoverage * RENTPERLEVELOFWIFICOVERAGE + numOfVendingMachines * RENTOFVENDINGMACHINE;
}

//increase the wifi coverage by 1
void BuildableProperty::increaseWifiCoverage()
{
    ++levelOfWifiCoverage;
}

//increase the number of vending machine
void BuildableProperty::addVendingMachines()
{
    ++numOfVendingMachines;
}

//return the cost of each level of wifi coverage
unsigned BuildableProperty::getCostPerLevelOfWifiCoverage()
{
    return COSTPERLEVELOFWIFICOVERAGE;
}

//return the cost per vending machine
unsigned BuildableProperty::getCostOfVendingMachine()
{
    return COSTOFVENDINGMACHINE;
}

//return level of wifi coverage
unsigned BuildableProperty::getLevelOfWifiCoverage()
{
    return levelOfWifiCoverage;
}

//reuturn number of vending machine
unsigned BuildableProperty::getNumOfVendingMachines()
{
    return numOfVendingMachines;
}

//overridded function, reset the state of buildable Property
void BuildableProperty::resetter()
{
    Property::resetter();
    levelOfWifiCoverage = 0;
    numOfVendingMachines = 0;
}

//return information of buildable Property
QString BuildableProperty::getBoxInfo()
{
    return (Property::getBoxInfo() + "\nBase Rent price(without anything builded): " + QString::number(Property::getRentOfProperty()) + "\nExtra rent with each of level of wifi coverage: " + QString::number(RENTPERLEVELOFWIFICOVERAGE) + "\nExtra rent with vending Machine: " + QString::number(RENTOFVENDINGMACHINE) + "\nColor: " + (propertyColor == Red ? "Red" : (propertyColor == Blue ? "Blue" : (propertyColor == Yellow ? "Yellow" : "Green"))) + "\n" + "\nLevel of Wifi Coverage Now: " + QString::number(levelOfWifiCoverage) + "\nNumber of Vending Machine Now: " + QString::number(numOfVendingMachines));
}
