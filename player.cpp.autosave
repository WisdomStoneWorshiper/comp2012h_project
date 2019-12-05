#include "player.h"

Player::Player(const unsigned short id_num){
    id = id_num;
    money = 10000;
    gpa = 0.0;
    position = 0;
    state = NORMAL;
};

int Player::get_position(){
    return position;
}

float Player::get_gpa(){
    return gpa;
}

int Player::get_money(){
    return money;
}

Player& Player::operator+(int a){
    money+=a;
    return *this;
}

Player& Player::operator-(int a){
    money-=a;
    return *this;
}
