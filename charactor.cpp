#include "charactor.h"

Charactor::Charactor(unsigned short num):id(num){

}

Charactor::Charactor(const Charactor& charactor):id(charactor.id){
    owned_place_id_list=charactor.owned_place_id_list;
}

unsigned short Charactor::getId() const{
    return id;
}

void Charactor::addProperty(Property* name){
    owned_place_id_list.push_back(name->getId());
}

void Charactor::removeProperty(Property* name){
    vector<unsigned> ::const_iterator targetId=find_if(owned_place_id_list.begin(),owned_place_id_list.end(),
                                                       [&](const unsigned& id){return id==name->getId();});
    owned_place_id_list.erase(targetId);
}

vector <unsigned> Charactor::getOwnedPropertyList(){
    return owned_place_id_list;
}
