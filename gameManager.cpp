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
    deck->shuffle();
//    for (vector<Box*>::const_iterator target=gameField.begin();target!=gameField.end();++target){
//        if(typeid ((*target))==typeid (BuildableProperty)|| (typeid ((*target))==typeid (Restaurant))){
//            Property* temp=static_cast<Property*>(*target);
//            Box::connect(temp,SIGNAL(doMortgage(unsigned ,unsigned)),SLOT(mortgageAction(unsigned,unsigned)));
//        }
//    }
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
    if (checkBankrupt()){
        //vector<Player*>::const_iterator loser=find_if(playerList.begin(),playerList.end(),
          //                                            [&](const Player* target){return target->getId()==currentPlayer->getId();});
        QMessageBox* loseMsg=new QMessageBox();
        loseMsg->setText("Player"+QString::number(currentPlayer->getId())+" bankrupted! sosad");
        loseMsg->exec();
        for (int i=0;i<currentPlayer->getOwnedPropertyList().size();++i){
            Property* target=static_cast<Property*>(gameField[currentPlayer->getOwnedPropertyList()[i]]);
            target->resetter();
        }
        delete loseMsg;
    }

    do{
        if (currentPlayer!=playerList[numOfPlayer-1]){
            currentPlayer=playerList[currentPlayer->getId()];
        }
        else
            currentPlayer=playerList[0];
    }while (currentPlayer->checkLosed()) ;

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
            (*currentPlayer)-=bp->getRentOfProperty();
            qDebug()<<"t5";
           // vector<Player*>::const_iterator owner=find_if(playerList.begin(),playerList.end(),
             //                          [&](Player* p){return p->getId()==bp->getOwnerId();});
            Player* owner=playerList[bp->getOwnerId()-1];
            qDebug()<<"rent"<<currentPlayer->getId()<<owner->getId()<<bp->getName()<<bp->getId();
            (*owner)+=(bp->getRentOfProperty());
            qDebug()<<"t7";
            rentMessage->setInformativeText("You have to pay $"+QString::number(bp->getRentOfProperty())+"for rent.");
            qDebug()<<"t8";
            rentMessage->exec();
//            int choice=rentMessage->exec();
//            if (choice==QMessageBox::Ok){

//            }
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
            qDebug()<<"rent"<<currentPlayer->getId()<<owner->getId()<<r->getName()<<r->getId();
            (*currentPlayer)-=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t6";
            (*owner)+=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t7";
            rentMessage->setInformativeText(r->getName()+" is owned by other player\nYou have to pay $"+QString::number(r->getRentOfProperty(numOfRestaurant-1))+" for rent.");
            qDebug()<<"t8";
            rentMessage->exec();
//            int choice=rentMessage->exec();
//            if (choice==QMessageBox::Ok){

//            }
        }
    }else if(QString::compare((b)->getName(),"Email",Qt::CaseInsensitive)==0){
        emailAction(b);
    }else if(QString::compare((b)->getName(),"TakeTheClass",Qt::CaseInsensitive)==0){

        QMessageBox popUpContent;
        popUpContent.setInformativeText("According to your disappointing mid-term result\n"
                                         "\n"
                                         "You have to take the make-up class now\n"
                                         "\n"
                                         "Roll the dice with 6 help you esacpe the class\n"
                                         "\n"
                                         "Or pay $500 after you fail 3 round in rolling 6");
        popUpContent.setStandardButtons(QMessageBox::Ok);
        popUpContent.setDefaultButton(QMessageBox::Ok);
        popUpContent.exec();

        currentPlayer->setinJail(true);
        movePlayer(14);

    }
    delete rentMessage;
    qDebug()<<"t9";
}

void GameManager::playerPositionSetter(Player *p, Box *b){
    //if (b->getId()<7){
    qDebug()<<p->getId()<<b->getName();
    qDebug()<<currentPlayer->getJailPass();
    qDebug()<<"c9";

    if (currentPlayer->getJailPass() && p->checkInJail()){
        currentPlayer->setinJail(false);
        currentPlayer->changeJailPass();

        QMessageBox usePassMsg;
        usePassMsg.setText("Lucky! You have a \"Escape Pass\", You can leave in next round\n\nNow You have no \"Escape Pass\"");
        usePassMsg.exec();
    }
    if (!(p->checkInJail())){
        qDebug()<<"p2";
        if (p->getId()<4){
            qDebug()<<"p3"<<b->getP1XPosition()<<b->getP1YPosition();
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        }else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()+50);
    }else{
            if (p->getId()<4)
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-1),static_cast<Jail*>(b)->getJailP1YPosition());
            else
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-4),static_cast<Jail*>(b)->getJailP1YPosition()-50);
            qDebug()<<"p8";
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

bool GameManager::ableToIncreaseWifi(){
    //vector<Box*>::const_iterator b=find_if(gameField.begin(),gameField.end(),
      //                                   [&](Box* target){return target->getId()==currentPlayer->getPosition();});
    Box* b=gameField[currentPlayer->getPosition()];

    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostPerLevelOfWifiCoverage() && p->getLevelOfWifiCoverage()<4);
    }
    return false;
}

bool GameManager::ableToAddVendingMachine(){
    Box* b=gameField[currentPlayer->getPosition()];
    qDebug()<<"av"<<(typeid ((*b))==typeid (BuildableProperty));
    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostOfVendingMachine() && p->getNumOfVendingMachines()<1 && p->getLevelOfWifiCoverage()==4);
    }
    return false;
}

bool GameManager::checkEndTurn(){
    if(!ableToBuy()&&!ableToIncreaseWifi()) return true;
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

void GameManager::build(){
    BuildableProperty* bp=static_cast<BuildableProperty*>(gameField[currentPlayer->getPosition()]);
    if (ableToAddVendingMachine()){
        (*currentPlayer)-=bp->getCostOfVendingMachine();
        bp->addVendingMachines();
    }else if (ableToIncreaseWifi()){
        (*currentPlayer)-=bp->getCostPerLevelOfWifiCoverage();
        bp->increaseWifiCoverage();
    }

}

void GameManager::emailAction(Box* oldLocation){



    Email * e=deck->getEmail();
    QMessageBox * emailContent=new QMessageBox();

    emailContent->setInformativeText(e->getMessage());
    emailContent->setStandardButtons(QMessageBox::Ok);
    emailContent->setDefaultButton(QMessageBox::Ok);
    //emailContent->exec();
    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    int choice=emailContent->exec();
    if (choice==QMessageBox::Ok){

        e->emailAction(currentPlayer);
    }

    if(deck->isCompletelyUsed()){
        deck->shuffle();
    }else qDebug()<<"not completely Used the deck";

    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    //vector<Box*>::const_iterator newLocation=find_if(gameField.begin(),gameField.end(),
      //                                   [&](Box* b){return b->getId()==currentPlayer->getPosition();});
    Box* newLocation=gameField[currentPlayer->getPosition()];
    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    qDebug()<<"et1";

//    if (currentPlayer->getJailPass()){

//        currentPlayer->setinJail(false);
//        currentPlayer->changeJailPass();
//        QMessageBox* usePassMsg=new QMessageBox();
//        usePassMsg->setText("You have used the pass");
//        usePassMsg->exec();
//    }

    if (oldLocation->getId()<(newLocation)->getId()){
        qDebug()<<"et2";
        qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
        playerPositionSetter(currentPlayer,newLocation);
    }else if(oldLocation->getId()>(newLocation)->getId()){
        qDebug()<<"et3";
        (*currentPlayer)+=2000;
        qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
        playerPositionSetter(currentPlayer,newLocation);
    }
    delete emailContent;

}

QString GameManager::getCurrentPlayerInfo(){
    qDebug()<<"Info"<<("Player id: "+QString::number(currentPlayer->getId())
              +"\nPlayer name: "+currentPlayer->getName()
              +"\n$: "+QString::number(currentPlayer->getMoney())
              +"\nJail Pass on hand? "+((currentPlayer->getJailPass())?"Yes":"No"));

    return (currentPlayer->getPlayerInfo());
}

unsigned GameManager::getMoneyAfterBuy(){
    return currentPlayer->getMoney()-static_cast<Property*>(gameField[currentPlayer->getPosition()])->getPropertyPrice();
}

unsigned GameManager::getMoneyAfterBuild(){
    BuildableProperty* target=static_cast<BuildableProperty*>(gameField[currentPlayer->getPosition()]);
    if (ableToAddVendingMachine())
        return currentPlayer->getMoney()-target->getCostOfVendingMachine();
    else
        return currentPlayer->getMoney()-target->getCostPerLevelOfWifiCoverage();
}

vector<Player*> GameManager::getPlayerList() const{
    return playerList;
}

vector<Box*> GameManager::getGameField() const{
    return gameField;
}

void GameManager::tradeAction(Player* seller,Property*targetProperty,unsigned price){
    currentPlayer->addProperty(targetProperty);
    seller->removeProperty(targetProperty);
    (*currentPlayer)-=price;
    (*seller)+=price;
}

void GameManager::mortgageAction(Property *target, int mod){
    if (mod==Apply){
        target->setMortgage(true);
        (*currentPlayer)+=target->getPropertyPrice()/2;
    }else if (mod==Pay){
        target->setMortgage(false);
        (*currentPlayer)-=target->getPropertyPrice()/2*1.1;
    }
}

bool GameManager::checkBankrupt(){
    return currentPlayer->getMoney()<0;
}

int GameManager::winner(){
    int alivePlayerId=0, totalPlayerAlive=0;
    for (int i=0;i<playerList.size();++i){
        if (playerList[i]->checkLosed()==false && totalPlayerAlive>0){
            return -1;
        }else if (playerList[i]->checkLosed()==false){
            alivePlayerId=playerList[i]->getId();
            ++totalPlayerAlive;
        }
    }
    return alivePlayerId;
}

bool GameManager::haveArrestToSell(){
    if (currentPlayer->getOwnedPropertyList().size()>0)
        return true;
    return false;
}
