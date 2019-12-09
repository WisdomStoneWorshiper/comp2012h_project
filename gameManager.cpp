#include "gameManager.h"


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

}
void GameManager::moveToNextPlayer(){


}
void GameManager::movePlayer(unsigned u){

}

