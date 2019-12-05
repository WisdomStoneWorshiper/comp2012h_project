#include "charactor.h"

Charactor::Charactor(){

}

Charactor::Charactor(Charactor& charactor){
    owned_place=charactor.owned_place;
}

void Charactor:: add_property(Property name){
    owned_place.push_back(name);
}
