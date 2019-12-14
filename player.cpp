#include "player.h"
#include <QDebug>

Player::Player(unsigned short id_num, QString name): id(id_num){
    money = 10000;
    position = 0;
    qDebug()<<"c2";
    jail_pass = false;
    qDebug()<<"c3"<<jail_pass;
    user_name = name;
    inJail=false;
    jailDiceCount[0]=0;
    jailDiceCount[1]=0;
    losed=false;
};

Player::Player(const Player& player):id(player.id){
    owned_place_id_list = player.owned_place_id_list;
    money = player.getMoney();
    money=player.getMoney();
    owned_place_id_list=player.owned_place_id_list;
    jail_pass=player.jail_pass;
    user_name = player.getName();
    position = player.position;
    inJail=player.inJail;
}

unsigned short Player::getId() const{
    return id;
}

void Player::addProperty(Property* name){
    owned_place_id_list.push_back(name->getId());
}

void Player::removeProperty(Property* name){
    vector<unsigned> ::const_iterator targetId=find_if(owned_place_id_list.begin(),owned_place_id_list.end(),
                                                       [&](const unsigned& id){return id==name->getId();});
    owned_place_id_list.erase(targetId);
}

vector <unsigned> Player::getOwnedPropertyList() const{
    return owned_place_id_list;
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event){

    msgBox.setText(this->getPlayerInfo());
   // qDebug()<<this->getBoxInfo();
   // qDebug()<<"I am ready!"<<msgBox.text()<<"done";
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);
}

QString Player::getPlayerInfo() const{
    return ("Player Id: "+QString::number(this->getId())
                +"\nPlayer name: "+this->getName()
                +"\n$: "+QString::number(this->getMoney())
                +"\nJail Pass on hand? "+((this->getJailPass())?"Yes":"No"));
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

bool Player:: checkInJail() const{
    return inJail;
}

void Player::setinJail(bool state){
    inJail = state;
}


void Player::setmoney(int a){
    money = a;
}


void Player::setNumOfRestaurant(unsigned int r){
    numOfRestaurant=r;
}

unsigned Player::getNumOfRestaurant(){
    return numOfRestaurant;
}

void Player::saveJailDice(unsigned num){
    QMessageBox* jailMessage=new QMessageBox();

    if (jailDiceCount[0]==0){
        jailDiceCount[0]=num;
        jailMessage->setText("Fail to Roll a SIX, \n\nYou still in jail");
    }else if(jailDiceCount[0]!=0 && jailDiceCount[1]==0){
        if(jailDiceCount[0]==num){
            inJail=false;
            jailDiceCount[0]=0;
            jailMessage->setText("You will be released in next round");
            setinJail(false);
        }else{
            jailDiceCount[1]=num;
            jailMessage->setText("Fail to Roll a SIX, \n\nYou still in jail");

        }
    }else{
        if(!(jailDiceCount[0]==num||jailDiceCount[1]==num)){
            //inJail==false;
            //jailDiceCount[0]=jailDiceCount[1]=0;
            money-=500;
            jailMessage->setText("You have been the jail 3 round already\n\nYou will be released in next round but you need to pay $500 fine now");
            setinJail(false);
        }else{
            jailMessage->setText("You roll a SIX!\n\nYou will be released in next round");
            setinJail(false);
        }
        inJail=false;
        jailDiceCount[0]=jailDiceCount[1]=0;
    }
    int ok=jailMessage->exec();
    if (ok==QMessageBox::Ok){
        delete jailMessage;
    }
    //jailDiceCount[0]=jailDiceCount[1]=0;

}

bool Player::checkLosed() const{
    return losed;
}

void Player::setLosed(){
    losed=true;
}
