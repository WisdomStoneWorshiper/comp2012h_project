#include "player.h"

Player::Player(unsigned short id_num):Charactor(id_num){
    money = 10000;
    gpa = 0.0;
    state = NORMAL;
    jail_pass = false;
};

Player::Player(Player& player):Charactor(player.getId()){
    gpa=player.getGpa();
    money=player.getMoney();
    state=player.state;
    owned_place=player.owned_place;
    jail_pass =  player.getJailPass();
}

float Player::getGpa(){
    return gpa;
}

int Player::getMoney(){
    return money;
}

bool Player::getJailPass(){
    return jail_pass;
}

bool Player::buyProperty(Property* target){
<<<<<<< HEAD
=======

>>>>>>> 2e75d4f210f0d071075799ac69daeb3830c4e57d
    if(target->getPropertyPrice()>money){
        return false;
    }
    money -= target->getPropertyPrice();

    addProperty(target);
    target->changeOwner(getId());
<<<<<<< HEAD
=======

>>>>>>> 2e75d4f210f0d071075799ac69daeb3830c4e57d
    return true;
}

Player& Player::operator+(int a){
    money+=a;
    return *this;
}

Player& Player::operator-(int a){
    money-=a;
    return *this;
}
