#include "banker.h"


Banker::Banker(unsigned short num):Charactor(num){

}

Banker::Banker(const Banker& b):Charactor(b.getId()){
    mortgageId_list = b.mortgageId_list;
    owned_place_id_list = b.owned_place_id_list;
}

Banker::~Banker(){
    mortgageId_list.clear();
}

void Banker::addMortgage(Property * name){
    mortgageId_list.push_back(name->getId());
}

void Banker::foreclosure(Property * name){
    vector<unsigned> ::const_iterator targetId=find_if(mortgageId_list.begin(),mortgageId_list.end(),
                                                       [&](const unsigned& id){return id==name->getId();});
    mortgageId_list.erase(targetId);
}

