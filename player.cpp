#include "player.h"

Player::Player(unsigned short id_num, QString name):Charactor(id_num){
    money = 10000;
    gpa = 0.0;
    state = NORMAL;
    jail_pass = false;
    user_name = name;
};

Player::Player(const Player& player):Charactor(player.getId()){
    gpa=player.getGpa();
    money=player.getMoney();
    state=player.state;
    owned_place=player.owned_place;
    jail_pass =  player.getJailPass();
    user_name = player.getName();
}

float Player::getGpa() const{
    return gpa;
}

int Player::getMoney() const{
    return money;
}

bool Player::getJailPass() const{
    return jail_pass;
}

QString Player::getName() const{
    return user_name;
}
bool Player::buyProperty(Property* target){
    if(target->getPropertyPrice()>money){
        return false;
    }
    money -= target->getPropertyPrice();
    addProperty(target);
    target->changeOwner(getId());
    return true;
}

void Player::changeJailPass(){
    if(getJailPass() == false){
        jail_pass = true;
    }else{
        jail_pass = false;
    }
}
Player& Player::operator+(int a){
    money+=a;
    return *this;
}

Player& Player::operator-(int a){
    money-=a;
    return *this;
}
