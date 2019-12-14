#include "character.h"
#include <QDebug>

Character::Character(unsigned short num, QString name):id(num){
    money = 10000;
    position = 0;
    state = NORMAL;
    qDebug()<<"c2";
    jail_pass = false;
    qDebug()<<"c3"<<jail_pass;
    user_name = name;
    inJail=false;
    jailDiceCount[0]=0;
    jailDiceCount[1]=0;
    losed=false;
}

Character::Character(const Character& character):id(character.id){
    owned_place_id_list = character.owned_place_id_list;
    money = character.getMoney();
    state = character.state;
    owned_place_id_list = character.owned_place_id_list;
    jail_pass = character.jail_pass;
    user_name = character.getName();
    position = character.position;
    inJail = character.inJail;
}

unsigned short Character::getId() const{
    return id;
}

vector <unsigned> Character::getOwnedPropertyList() const{
    return owned_place_id_list;
}

int Character::getMoney() const{
    return money;
}

void Character::setmoney(int a){
    money = a;
}

bool Character::getJailPass() const{
    qDebug()<<"c10";
    //macbook user can't return jail_pass, don't know do what
    //return jail_pass;
    return jail_pass;
}

QString Character::getName() const{
    return user_name;
}

unsigned short Character::getPosition() const{
    return position;
}


void Character::addProperty(Property* name){
    owned_place_id_list.push_back(name->getId());
}

void Character::removeProperty(Property* name){
    vector<unsigned> ::const_iterator targetId=find_if(owned_place_id_list.begin(),owned_place_id_list.end(),
                                                       [&](const unsigned& id){return id==name->getId();});
    owned_place_id_list.erase(targetId);
}

