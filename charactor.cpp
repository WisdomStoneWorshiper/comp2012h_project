#include "charactor.h"

Charactor::Charactor(unsigned short num):id(num){

}

Charactor::Charactor(const Charactor& charactor):id(charactor.id){
    owned_place=charactor.owned_place;
}

unsigned short Charactor::getId() const{
    return id;
}

void Charactor::addProperty(Property* name){
    owned_place.push_back(name);
}

void Charactor::removeProperty(Property* name){
    //owned_place.remove(name);
}

vector <Property*> Charactor::getOwnedPropertyList(){
    return owned_place;
}
