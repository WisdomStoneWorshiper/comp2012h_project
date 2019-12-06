#include "banker.h"


Banker::Banker(unsigned short num):Charactor(num){

}

Banker::Banker(const Banker& b):Charactor(b.getId()){
    mortgage_list = b.mortgage_list;
    owned_place = b.owned_place;
}

void Banker::addMortgage(Property * name){
    mortgage_list.push_back(name);
}

void Banker::foreclosure(Property * name){
    mortgage_list.remove(name);
}
