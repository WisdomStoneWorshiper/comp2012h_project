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
    jailTurnCounter=0;
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

Player::~Player(){
    owned_place_id_list.clear();
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
                +"\nJail Pass on hand? "+((this->getJailPass())?"Yes":"No")
                +"\n\nState: " + (inJail?"Imprisonnment":"Out of Jail"));
}


int Player::getMoney() const{
    return money;
}

bool Player::getJailPass() const{
    qDebug()<<"c10";

    //return jail_pass;

    return 1;

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
          setJail_pass(true);
//        jail_pass = true;
    }else{
        setJail_pass(false);
//        jail_pass = false;
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
void Player::setJail_pass(bool own){
    jail_pass = own;
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
            setinJail(false);
            jailTurnCounter=0;
        }
    }else{
            jailMessage->setText("You Roll a Six, You will be released in next round");
            setinJail(false);
            jailTurnCounter=0;          
    }
    int ok=jailMessage->exec();
    if (ok==QMessageBox::Ok){
        delete jailMessage;
    }
    //jailDiceCount[0]=jailDiceCount[1]=0;
      delete jailMessage;
}

bool Player::checkLosed() const{
    return losed;
}

void Player::setLosed(){
    losed=true;
}
