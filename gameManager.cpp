#include "gameManager.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>

GameManager::GameManager(){

}

GameManager::~GameManager(){

}

void GameManager::init(unsigned num,  list<Box*> boxList, list<Player*> playerList){
    numOfPlayer=num;
    this->playerList=playerList;
    gameField=boxList;
    currentPlayer=this->playerList.front();
}

void GameManager::setCurrentPlayer(Player* p){
    currentPlayer=p;
}

void GameManager:: moveToNextPlayer(){
    list<Player *>::const_iterator p=find(playerList.begin(),playerList.end(),currentPlayer);
    if (currentPlayer!=playerList.back()){
        currentPlayer=*(++p);
    }
    else
        currentPlayer=playerList.front();
}

void GameManager::mavePlayer(unsigned int targetBoxId){

}

int GameManager::rollDice(){
    return 0;
}

