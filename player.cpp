#include "player.h"

Player::Player(unsigned short id_num, QString name):Charactor(id_num){
    money = 10000;
    position = 0;
    gpa = 0.0;
    state = NORMAL;
    jail_pass = false;
    user_name = name;
    inJail=false;
};

Player::Player(const Player& player):Charactor(player.getId()){
    gpa=player.getGpa();
    money=player.getMoney();
    state=player.state;
    owned_place=player.owned_place;
    jail_pass =  player.getJailPass();
    user_name = player.getName();
    position = player.position;
    inJail=player.inJail;
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

unsigned short Player::getPosition() const{
    return position;
}

void Player::setPosition(unsigned short pos){
    position = pos;
}

void Player::changeJailPass(){
    if(getJailPass() == false){
        jail_pass = true;
    }else{
        jail_pass = false;
    }
}
Player& Player::operator+=(int a){
    money+=a;
    return *this;
}

Player& Player::operator-=(int a){
    money-=a;
    return *this;
}

bool Player:: checkInJail(){
    return inJail;
}

void Player::setinJail(bool state){
    inJail=state;

void Player::setGpa(float points){
    gpa = points;
}

void Player::setState(STATE a){
    state = a;
}

void Player::setmoney(int a){
    money = a;
}

void Player::setSchool(SCHOOL a){
    school = a;

}
