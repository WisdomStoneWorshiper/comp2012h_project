#include "player.h"

Player::Player(unsigned short id_num):id(id_num){
    money = 10000;
    gpa = 0.0;
    state = NORMAL;
};

Player::Player(Player& player):id(player.get_id()){
    gpa=player.get_gpa();
    money=player.get_money();
    state=player.state;
    owned_place=player.owned_place;
}

float Player::get_gpa(){
    return gpa;
}

int Player::get_money(){
    return money;
}

unsigned short Player::get_id(){
    return id;
}

bool Player::buy_property(Property target){
    if(target.getPropertyPrice()>money){
        return false;
    }
    money -= target.getPropertyPrice();
    add_property(target);
    target.changeOwner(get_id());
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
