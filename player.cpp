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

unsigned short Player::getId() const{  //access the user unique id
    return id;
}

void Player::addProperty(Property* name){  //put the property to the own property vector
    owned_place_id_list.push_back(name->getId());
}

void Player::removeProperty(Property* name){ //remove the property from the own property vector
    vector<unsigned> ::const_iterator targetId=find_if(owned_place_id_list.begin(),owned_place_id_list.end(),
                                                       [&](const unsigned& id){return id==name->getId();});  //use the property id to find the property form vector
    owned_place_id_list.erase(targetId);
}

vector <unsigned> Player::getOwnedPropertyList() const{ //access the property vector
    return owned_place_id_list;
}

void Player::mousePressEvent(QGraphicsSceneMouseEvent *event){ //show the player information when mouse pressed

    msgBox.setText(this->getPlayerInfo());
   // qDebug()<<this->getBoxInfo();
   // qDebug()<<"I am ready!"<<msgBox.text()<<"done";
    msgBox.exec();
    QGraphicsItem::mousePressEvent(event);
}

QString Player::getPlayerInfo() const{  //set the format of player information when showed
    return ("Player Id: "+QString::number(this->getId())
                +"\nPlayer name: "+this->getName()
                +"\n$: "+QString::number(this->getMoney())
                +"\nJail Pass on hand? "+((this->getJailPass())?"Yes":"No")
                +"\n\nState: " + (inJail?"Imprisonnment":"Out of Jail"));
}


int Player::getMoney() const{  //access player money
    return money;
}

bool Player::getJailPass() const{  //access player jail pass
    qDebug()<<"c10";

    //macbook user can't return jail_pass, don't know do what
    //return jail_pass;

    return jail_pass; //true = have jail pass

}

QString Player::getName() const{  //access player name
    return user_name;
}
bool Player::buyProperty(Property* target){  //player buy the property

    if(target->getPropertyPrice()>money){ //check whether the player has enough money to buy the property
        return false;
    }
    money -= target->getPropertyPrice();

    addProperty(target);
    target->changeOwner(getId());

    return true;
}

unsigned short Player::getPosition() const{  //access the player current position
    return position;
}

void Player::setPosition(unsigned pos){  //change the player position
    position = pos;
}

void Player::changeJailPass(){  //trigger to change the jail pass boolean
    if(jail_pass==false){  // when player get jail pass
        qDebug()<<" Player::changeJailPass() true\n";
          qDebug()<<this->getPlayerInfo();

        jail_pass = true;
    }else{  //when user use the jail pass
        jail_pass = false;

          qDebug()<<" Player::changeJailPass() false";

    }
}
Player& Player::operator+=(int a){ //use operator to add money from player
    money+=a;
    return *this;
}

Player& Player::operator-=(int a){ //use operator to subtract money from player
    money-=a;
    return *this;
}

bool Player:: checkInJail() const{  //check whether the player is in jail
    return inJail;
}

void Player::setinJail(bool state){  //when the player go into jail
    inJail = state;
}


void Player::setmoney(int a){  //set the player money directly
    money = a;
}


void Player::setNumOfRestaurant(unsigned int r){ //change the number of restaurant
    numOfRestaurant=r;
}
void Player::setJail_pass(bool own){
    jail_pass = own;
}


unsigned Player::getNumOfRestaurant(){  //change the number of restaurant
    return numOfRestaurant;//88
}

void Player::jailAction(unsigned num){  //the principle of jail
    QMessageBox* jailMessage=new QMessageBox();
    if (num!=6){
        if (jailTurnCounter<2){  //if player cannot roll a six in two round
            ++jailTurnCounter;  //stored how many round player can't roll a six
            jailMessage->setText("Fail to Roll a SIX, \n\nYou still in jail");
        }else{ //if player have already roll dice for three round and can't get a six in round three
            money-=500;  //pay money to released the jail
            jailMessage->setText("You have been the jail 3 round already\n\nYou will be released in next round but you need to pay $500 fine now");
            setinJail(false);
            jailTurnCounter=0;  //reset the round counter
        }
    }else{  //if the player roll a six
            jailMessage->setText("You Roll a Six, You will be released in next round");
            setinJail(false);  //the player no longer in jail
            jailTurnCounter=0; //reset the round counter
    }
    int ok=jailMessage->exec();
    if (ok==QMessageBox::Ok){
        delete jailMessage;
    }
    //jailDiceCount[0]=jailDiceCount[1]=0;
     // delete jailMessage;
}

bool Player::checkLosed() const{ //check whether the player is losed
    return losed;
}

void Player::setLosed(){ //set when player is losed
    losed=true;
}
