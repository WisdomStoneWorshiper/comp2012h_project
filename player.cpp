#include "player.h"

Player::Player(unsigned short id_num, QString name):Charactor(id_num){
    money = 10000;
    position = 0;
    gpa = 0.0;
    state = NORMAL;
    jail_pass = false;
    user_name = name;
    inJail=false;
    jailDiceCount[0]=0;
    jailDiceCount[1]=0;
};

Player::Player(const Player& player):Charactor(player){
    gpa=player.getGpa();
    money=player.getMoney();
    state=player.state;
    owned_place=player.owned_place;
    jail_pass =  player.getJailPass();
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
    return ("Player id: "+QString::number(this->getId())
                +"\nPlayer name: "+this->getName()
                +"\n$: "+QString::number(this->getMoney())
                +"\nJail Pass on hand? "+((this->getJailPass())?"Yes":"No"));
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

void Player::setPosition(unsigned pos){
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

void Player::saveJailDice(unsigned num){
    QMessageBox* jailMessage=new QMessageBox();

    if (jailDiceCount[0]==0){
        jailDiceCount[0]=num;
        jailMessage->setText("You still in jail");
    }else if(jailDiceCount[0]!=0 && jailDiceCount[1]==0){
        if(jailDiceCount[0]==num){
            inJail==false;
            jailDiceCount[0]=0;
            jailMessage->setText("You release now");
        }else{
            jailDiceCount[1]=num;
            jailMessage->setText("You still in jail");
        }
    }else{
        if(!(jailDiceCount[0]==num||jailDiceCount[1]==num)){
            //inJail==false;
            //jailDiceCount[0]=jailDiceCount[1]=0;
            money-=500;
            jailMessage->setText("You release now but you need to pay $500 fine");
        }else{
            jailMessage->setText("You release now");
        }
        inJail==false;
        jailDiceCount[0]=jailDiceCount[1]=0;
    }
    int ok=jailMessage->exec();
    if (ok==QMessageBox::Ok){
        delete jailMessage;
    }
    //jailDiceCount[0]=jailDiceCount[1]=0;

}
