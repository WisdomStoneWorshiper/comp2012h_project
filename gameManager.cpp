#include "gameManager.h"
#include <QDebug>

GameManager::GameManager():timer(new QElapsedTimer()){

}

GameManager::~GameManager(){

}

void GameManager::init(unsigned num,  list<Box*> boxList, list<Player*> playerList){
    numOfPlayer=num;
    gameField=boxList;
    this->playerList=playerList;
    currentPlayer=this->playerList.front();
}

void GameManager::setCurrentPlayer(Player*p){
    currentPlayer=p;
}

Player* & GameManager::getCurrentPlayer(){
    return currentPlayer;
}
void GameManager::moveToNextPlayer(){
        list<Player *>::const_iterator p=find(playerList.begin(),playerList.end(),currentPlayer);
        if (currentPlayer!=playerList.back()){
            qDebug()<<"m"<<(*p)->getId();
            currentPlayer=*(++p);
            qDebug()<<(*p)->getId();
        }
        else
            currentPlayer=playerList.front();
}
void GameManager::movePlayer(unsigned u){
    //QPropertyAnimation* an=new QPropertyAnimation(currentPlayer,"fs");
    //currentPlayer->setPosition(5);
    list<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    //currentPlayer->setPos(currentPlayer->x()+100,currentPlayer->y());
    for (int i=0;i<u;++i){
        if ((*b)->getId()==27){
            (*currentPlayer)+=2000;
            b=gameField.begin();
        }else ++b;
    }

    qDebug()<<"gm"<<(*b)->getName();
//    timer->restart();
//    unsigned frame=0;
//    double currX=currentPlayer->x(),currY=currentPlayer->y();
//    while(timer->elapsed()<1000){
//        if(timer->elapsed()/17>frame){
//            ++frame;
//            currentPlayer->setPos(currX+int(((*b)->x()-currX)/60*frame),currY+((*b)->y()-currY)/60*frame);
//        }
//    }
    //currentPlayer->setPos((*b)->getP1XPosition(),(*b)->getP1YPosition());
    playerPositionSetter(currentPlayer,*b);
    currentPlayer->setPosition((*b)->getId());
}

void GameManager::playerPositionSetter(Player *p, Box *b){
    //if (b->getId()<7){
    if (b->getName()!="Jail"){
        if (p->getId()<4)
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()-50);
    }else{
        if (!p->checkInJail()){
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        }else{

            if (p->getId()<4)
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-1),static_cast<Jail*>(b)->getJailP1YPosition());
            else
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-4),static_cast<Jail*>(b)->getJailP1YPosition()-50);
        }
    }
//    }else if (b->getId()<14){
//        if (p->getId()<4)
//            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
//        else
//            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()-50);
//    }else if (b->getId()<21){

//    }else{

//    }
}

bool GameManager::ableToBuy(){
    list<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    qDebug()<<typeid (*(*b)).name()<<' '<<typeid (BuildableProperty).name();
    if(typeid (*(*b))==typeid (BuildableProperty)||typeid (*(*b))==typeid (Restaurant)){
        Property *p=static_cast<Property*>(*b);
        qDebug()<<currentPlayer->getMoney()<<" "<<p->getPropertyPrice()<<" "<<p->getOwnerId();
        return (currentPlayer->getMoney()>=p->getPropertyPrice() && p->getOwnerId()==0);
    }
    return false;
}

bool GameManager::ableToBuild(){
    list<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    if(typeid (*(*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(*b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostPerLevelOfWifiCoverage() && p->getLevelOfWifiCoverage()<4);
    }
    return false;
}

bool GameManager::checkEndTurn(){
    if(!ableToBuy()&&!ableToBuild()) return true;
    return false;
}

void GameManager::buyAsset(){
    list<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    if(typeid (*(*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(*b);
        currentPlayer->buyProperty(p);
    }else{
        Restaurant *r=static_cast<Restaurant*>(*b);
        currentPlayer->buyProperty(r);
    }
}
