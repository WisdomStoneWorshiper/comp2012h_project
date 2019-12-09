#include "gameManager.h"
#include <QDebug>

GameManager::GameManager(){

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
    list<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),[&](Box* b){return b->getId()==currentPlayer->getPosition();});
    //currentPlayer->setPos(currentPlayer->x()+100,currentPlayer->y());
    for (int i=0;i<u;++i,++b);

    qDebug()<<"gm"<<(*b)->getName();
}

//bool GameManager::findCurrentBox(Box *t){
//    return t->getId()==currentPlayer->getPosition();
//}
