#include "player.h"
#include <QDebug>

Player::Player(unsigned short id_num, QString name):Charactor(id_num){
    money = 10000;
    position = 0;
    gpa = 0.0;
    state = NORMAL;
    qDebug()<<"c2";
    jail_pass = false;
    qDebug()<<"c3"<<jail_pass;
    user_name = name;
    inJail=false;
    jailTurnCounter=0;
    losed=false;
};

Player::Player(const Player& player):Charactor(player){
    gpa=player.getGpa();
    money=player.getMoney();
    state=player.state;
    owned_place_id_list=player.owned_place_id_list;
    jail_pass=player.jail_pass;
    user_name = player.getName();
    position = player.position;
    inJail=player.inJail;
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event){

    msgBox.setText(this->getPlayerInfo());
   // qDebug()<<this->getBoxInfo();
   // qDebug()<<"I am ready!"<<msgBox.text()<<"done";
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);
}

QString Player::getPlayerInfo(){
    return ("Player Id: "+QString::number(this->getId())
                +"\nPlayer name: "+this->getName()
                +"\n$: "+QString::number(this->getMoney())
                +"\nJail Pass on hand? "+((this->getJailPass())?"Yes":"No")
                +"\n\nState: " + (inJail?"Imprisonnment":"Out of Jail"));
}

float Player::getGpa() const{
    return gpa;
}

int Player::getMoney() const{
    return money;
}

bool Player::getJailPass() const{
    qDebug()<<"c10";
    //macbook user can't return jail_pass, don't know do what
    //return jail_pass;

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

void Player::setPosition(unsigned pos){
    position = pos;
}

void Player::changeJailPass(){
    if(jail_pass==false){
        qDebug()<<" Player::changeJailPass() true\n";
          qDebug()<<this->getPlayerInfo();
        jail_pass = true;
    }else{
        jail_pass = false;
          qDebug()<<" Player::changeJailPass() false";
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
}

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

void Player::setNumOfRestaurant(unsigned int r){
    numOfRestaurant=r;
}

unsigned Player::getNumOfRestaurant(){
    return numOfRestaurant;
}

void Player::jailAction(unsigned num){
    QMessageBox* jailMessage=new QMessageBox();
    if (num!=6){
        if (jailTurnCounter<2){
            ++jailTurnCounter;
            jailMessage->setText("Fail to Roll a SIX, \n\nYou still in jail");
        }else{
            money-=500;
            jailMessage->setText("You have been the jail 3 round already\n\nYou will be released in next round but you need to pay $500 fine now");
            setinJail(NORMAL);
            jailTurnCounter=0;
        }
    }else{
            jailMessage->setText("You will be released in next round");
            setinJail(NORMAL);
            jailTurnCounter=0;

    }
    int ok=jailMessage->exec();
    if (ok==QMessageBox::Ok){
        delete jailMessage;
    }
    //jailDiceCount[0]=jailDiceCount[1]=0;

}

bool Player::checkLosed(){
    return losed;
}

void Player::setLosed(){
    losed=true;
}
