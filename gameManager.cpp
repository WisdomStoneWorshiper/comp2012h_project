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
void GameManager::moveToNextPlayer(){
        list<Player *>::const_iterator p=find(playerList.begin(),playerList.end(),currentPlayer);
        if (currentPlayer!=playerList.back()){
            currentPlayer=*p+1;
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
        if ((*b)->getId()==27) b=gameField.begin();
        else ++b;
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
    if (b->getId()<7){
        if (p->getId()<4)
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()-50);
    }else if (b->getId()<14){
        if (p->getId()<4)
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()-50);
    }else if (b->getId()<21){

    }else{

    }
}
