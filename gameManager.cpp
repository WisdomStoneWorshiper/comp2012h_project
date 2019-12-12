#include "gameManager.h"
#include <QDebug>

GameManager::GameManager():deck(new EmailDeck())
                           , banker(new Banker(0))
{

}

GameManager::~GameManager(){
    if (!playerList.empty()) playerList.clear();
    if (!gameField.empty()) gameField.clear();
    if (banker!=nullptr) delete banker;
    if (deck!=nullptr) delete deck;
}


void GameManager::init(unsigned num,  vector<Box*> boxList, vector<Player*> playerList){
    numOfPlayer=num;
    gameField=boxList;
    this->playerList=playerList;
    currentPlayer=this->playerList.front();
    //deck->shuffle();
}

//void GameManager::setCurrentPlayer(Player*p){
//    currentPlayer=p;
//}

Player* & GameManager::getCurrentPlayer(){
    return currentPlayer;
}
void GameManager::moveToNextPlayer(){
//        vector<Player *>::const_iterator p=find_if(playerList.begin(),playerList.end(),
//                                                 [&](Player* q){ qDebug()<<q->getId()<<currentPlayer->getId();
//                return q->getId()==currentPlayer->getId();});
        if (currentPlayer!=playerList[numOfPlayer-1]){
//            qDebug()<<"m"<<(*p)->getId();
//            currentPlayer=*p;
//            qDebug()<<currentPlayer->getId();
//            qDebug()<<(*p)->getId();
            currentPlayer=playerList[currentPlayer->getId()];
        }
        else
            currentPlayer=playerList[0];
}

void GameManager::movePlayer(unsigned u){
    //QPropertyAnimation* an=new QPropertyAnimation(currentPlayer,"fs");
    //currentPlayer->setPosition(5);
    /*vector<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* c){return c->getId()==(currentPlayer->getPosition()+u)%28;})*/;
    Box* b=(gameField[(currentPlayer->getPosition()+u)%28]);
    if (currentPlayer->getPosition()>(b)->getId()) (*currentPlayer)+=2000;
    //currentPlayer->setPos(currentPlayer->x()+100,currentPlayer->y());
//    for (int i=0;i<u;++i){
//        if ((*b)->getId()==27){
//            if (currentPlayer->checkInJail()==false)
//                (*currentPlayer)+=2000;
//            b=gameField.begin();
//        }else ++b;
//    }

//    qDebug()<<"gm"<<(*b)->getName();
    playerPositionSetter(currentPlayer,b);
    currentPlayer->setPosition((b)->getId());
    QMessageBox* rentMessage=new QMessageBox();
    //emailContent->setInformativeText(e->getMessage());
    rentMessage->setStandardButtons(QMessageBox::Ok);
    rentMessage->setDefaultButton(QMessageBox::Ok);
    qDebug()<<"t1";
    if(typeid ((*b))==typeid (BuildableProperty)){
        qDebug()<<"t2";
        BuildableProperty *bp=static_cast<BuildableProperty*>(b);
        qDebug()<<"t3";
        if(bp->getOwnerId()!=0 && bp->getOwnerId()!=currentPlayer->getId() && !bp->getMortgage()){
            qDebug()<<"t4";
            currentPlayer-=bp->getRentOfProperty();
            qDebug()<<"t5";
           // vector<Player*>::const_iterator owner=find_if(playerList.begin(),playerList.end(),
             //                          [&](Player* p){return p->getId()==bp->getOwnerId();});
            Player* owner=playerList[bp->getOwnerId()-1];
            qDebug()<<"t6";
            (*owner)+=(bp->getRentOfProperty());
            qDebug()<<"t7";
            rentMessage->setInformativeText("You have to pay $"+QString::number(bp->getRentOfProperty())+"for rent.");
            qDebug()<<"t8";
            int choice=rentMessage->exec();
            if (choice==QMessageBox::Ok){

            }
        }
    }else if (typeid ((*b))==typeid (Restaurant)){
        qDebug()<<"t2";
        Restaurant *r=static_cast<Restaurant*>(b);
        qDebug()<<"t3";
        if(r->getOwnerId()!=0 && r->getOwnerId()!=currentPlayer->getId() && !r->getMortgage()){
            qDebug()<<"t4";
           // vector<Player*>::const_iterator owner=find_if(playerList.begin(),playerList.end(),
             //                          [&](Player* p){return p->getId()==r->getOwnerId();});
            Player* owner=playerList[r->getOwnerId()-1];
            qDebug()<<"t5";
//            int numOfRestaurant=count_if((*owner)->getOwnedPropertyList().begin(),(*owner)->getOwnedPropertyList().end(),
//                                              [&](Property* p){return typeid (*p)==typeid (Restaurant);});
            unsigned numOfRestaurant=owner->getNumOfRestaurant();
            qDebug()<<"t5.1";
            currentPlayer-=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t6";
            (*owner)+=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t7";
            rentMessage->setInformativeText("You have to pay $"+QString::number(r->getRentOfProperty(numOfRestaurant-1))+"for rent.");
            qDebug()<<"t8";
            int choice=rentMessage->exec();
            if (choice==QMessageBox::Ok){

            }
        }
    }else if(QString::compare((b)->getName(),"Email",Qt::CaseInsensitive)==0){
        emailAction(b);
    }else if(QString::compare((b)->getName(),"TakeTheClass",Qt::CaseInsensitive)==0){
        currentPlayer->setinJail(true);
        movePlayer(14);
    }
    delete rentMessage;
    qDebug()<<"t9";
}

void GameManager::playerPositionSetter(Player *p, Box *b){
    //if (b->getId()<7){
    qDebug()<<p->getId()<<b->getName();
    if (!(p->checkInJail())){
        qDebug()<<"p2";
        if (p->getId()<4){
            qDebug()<<"p3"<<b->getP1XPosition()<<b->getP1YPosition();
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        }else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()-50);
        qDebug()<<"p4";
    }else{
        qDebug()<<"p5";
//        if (!(p->checkInJail())){
//            qDebug()<<"p6"<<b->getP1XPosition()<<b->getP1YPosition();
//            double x=b->getP1XPosition(),y=b->getP1YPosition();
//            p->setPos(x+20*(p->getId()-1),y);
//        }else{
            qDebug()<<"p7";
            if (p->getId()<4)
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-1),static_cast<Jail*>(b)->getJailP1YPosition());
            else
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-4),static_cast<Jail*>(b)->getJailP1YPosition()-50);
            qDebug()<<"p8";
//        }
    }
    qDebug()<<"p9";
}

bool GameManager::ableToBuy(){
    //vector<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
        //                                 [&](Box* target){ qDebug()<<target->getId()<<currentPlayer->getPosition();
      //      return target->getId()==currentPlayer->getPosition();});
    Box* b=gameField[currentPlayer->getPosition()];
    qDebug()<<typeid ((*b)).name()<<typeid (BuildableProperty).name();
    if(typeid ((*b))==typeid (BuildableProperty)||typeid ((*b))==typeid (Restaurant)){
        Property *p=static_cast<Property*>(b);
        qDebug()<<currentPlayer->getMoney()<<" "<<p->getPropertyPrice()<<" "<<p->getOwnerId();
        return (currentPlayer->getMoney()>=p->getPropertyPrice() && p->getOwnerId()==0);
    }
    return false;
}

bool GameManager::ableToBuild(){
    //vector<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
      //                                   [&](Box* target){return target->getId()==currentPlayer->getPosition();});
    Box* b=gameField[currentPlayer->getPosition()];
    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostPerLevelOfWifiCoverage() && p->getLevelOfWifiCoverage()<4);
    }
    return false;
}

bool GameManager::checkEndTurn(){
    if(!ableToBuy()&&!ableToBuild()) return true;
    return false;
}

void GameManager::buyAsset(){
   // vector<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
     //                                    [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    Box* b=gameField[currentPlayer->getPosition()];
    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        currentPlayer->buyProperty(p);
    }else{
        Restaurant *r=static_cast<Restaurant*>(b);
        currentPlayer->buyProperty(r);
        currentPlayer->setNumOfRestaurant(currentPlayer->getNumOfRestaurant()+1);
    }
}

void GameManager::emailAction(Box* oldLocation){
    Email * e=deck->getEmail();
    QMessageBox * emailContent=new QMessageBox();
    emailContent->setInformativeText(e->getMessage());
    emailContent->setStandardButtons(QMessageBox::Ok);
    emailContent->setDefaultButton(QMessageBox::Ok);
    int choice=emailContent->exec();
    if (choice==QMessageBox::Ok){
        e->emailAction(currentPlayer);
    }
    //vector<Box*>::const_iterator newLocation=find_if(gameField.begin(),gameField.end(),
      //                                   [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    Box* newLocation=gameField[currentPlayer->getPosition()];
    qDebug()<<"et1";
    if (oldLocation->getId()<(newLocation)->getId()){
        qDebug()<<"et2";
        playerPositionSetter(currentPlayer,newLocation);
    }else if(oldLocation->getId()>(newLocation)->getId()){
        qDebug()<<"et3";
        currentPlayer+=2000;
        playerPositionSetter(currentPlayer,newLocation);
    }
    delete emailContent;

}

QString GameManager::getCurrentPlayerInfo(){
    qDebug()<<"Info"<<("Player id: "+QString::number(currentPlayer->getId())
              +"\nPlayer name: "+currentPlayer->getName()
              +"\n$: "+QString::number(currentPlayer->getMoney())
              +"\nJail Pass on hand? "+((currentPlayer->getJailPass())?"Yes":"No"));

    return ("Player id: "+QString::number(currentPlayer->getId())
            +"\nPlayer name: "+currentPlayer->getName()
            +"\n$: "+QString::number(currentPlayer->getMoney())
            +"\nJail Pass on hand? "+((currentPlayer->getJailPass())?"Yes":"No"));
}

void GameManager::inJailAction(){

}
