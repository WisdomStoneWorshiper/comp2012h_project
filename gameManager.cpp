#include "gameManager.h"
#include <QDebug>

GameManager::GameManager():timer(new QElapsedTimer())
                           , deck(new EmailDeck())
                           , banker(new Banker(0))
{

}

GameManager::~GameManager(){
    if (!playerList.empty()) playerList.clear();
    if (!gameField.empty()) gameField.clear();
    if (banker!=nullptr) delete banker;
    if (deck!=nullptr) delete deck;
}


void GameManager::init(unsigned num,  list<Box*> boxList, list<Player*> playerList){
    numOfPlayer=num;
    gameField=boxList;
    this->playerList=playerList;
    currentPlayer=this->playerList.front();
    deck->shuffle();
//    if (deck==nullptr){
//        deck=new EmailDeck();
//        //deck->shuffle();
//    }else{
//        //deck->shuffle();
//    }
//    if(banker==nullptr)
//        banker=new Banker(0);
//    else{
//        delete banker;
//        banker=new Banker(0);
//    }
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
            if (currentPlayer->checkInJail()==false)
                (*currentPlayer)+=2000;
            b=gameField.begin();
        }else ++b;
    }

    qDebug()<<"gm"<<(*b)->getName();
    playerPositionSetter(currentPlayer,*b);
    currentPlayer->setPosition((*b)->getId());
    if(typeid (*(*b))==typeid (BuildableProperty)){

        BuildableProperty *p=static_cast<BuildableProperty*>(*b);
        if(p->getOwnerId()!=0 && p->getOwnerId()!=currentPlayer->getId() && !p->getMortgage()){
            currentPlayer-=p->getRentOfProperty();
        }
    }else if (typeid (*(*b))==typeid (Restaurant)){
        Restaurant *r=static_cast<Restaurant*>(*b);
        if(r->getOwnerId()!=0 && r->getOwnerId()!=currentPlayer->getId() && !r->getMortgage()){
            list<Player*>::const_iterator owner=find_if(playerList.begin(),playerList.end(),
                                       [&](Player* p){return p->getId()==r->getOwnerId();});
            unsigned numOfRestaurant=count_if((*owner)->getOwnedPropertyList().begin(),(*owner)->getOwnedPropertyList().end(),
                                              [&](Property* p){return typeid (*p)==typeid (Restaurant);});
            currentPlayer-=r->getRentOfProperty(numOfRestaurant-1);
        }
    }else if(QString::compare((*b)->getName(),"Email",Qt::CaseInsensitive)==0){
        emailAction(b);
        if (currentPlayer->getPosition()>(*b)->getId()){
            movePlayer(currentPlayer->getPosition()-(*b)->getId());
        }else if(currentPlayer->getPosition()<(*b)->getId()){

        }
    }else if(QString::compare((*b)->getName(),"TakeTheClass",Qt::CaseInsensitive)==0){
        currentPlayer->setinJail(true);
        movePlayer(14);
    }
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

void GameManager::emailAction(list<Box*>::const_iterator oldLocation){
    Email * e=deck->getEmail();
    QMessageBox * emailContent=new QMessageBox();
    emailContent->setInformativeText(e->getMessage());
    emailContent->setStandardButtons(QMessageBox::Ok);
    emailContent->setDefaultButton(QMessageBox::Ok);
    int choice=emailContent->exec();
    if (choice==QMessageBox::Ok){
        e->emailAction(currentPlayer);
    }
    list<Box*>::const_iterator newLocation=find_if(gameField.begin(),gameField.end(),
                                         [&](Box* b){return b->getId()==currentPlayer->getPosition();});

    if ((*oldLocation)->getId()<(*newLocation)->getId()){
        playerPositionSetter(currentPlayer,*newLocation);
    }else if((*oldLocation)->getId()>(*newLocation)->getId()){
        currentPlayer+=2000;
        playerPositionSetter(currentPlayer,*newLocation);
    }
    delete emailContent;

}

QString GameManager::getCurrentPlayerInfo(){
    return ("Player id: "+QString::number(currentPlayer->getId())
            +"\nPlayer name: "+currentPlayer->getName()
            +"\n$: "+QString::number(currentPlayer->getMoney())
            +"\nJail Pass on hand? "+((currentPlayer->getJailPass())?"Yes":"No"));
}
