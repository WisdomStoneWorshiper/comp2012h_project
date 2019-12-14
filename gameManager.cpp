#include "gameManager.h"
#include <QDebug>

//convention constructor of GameManager
GameManager::GameManager():deck(new EmailDeck())
                           , banker(new Banker(0))
{
    gameFieldScene=nullptr;
}

//destructor of GameManager
GameManager::~GameManager(){
    if (!playerList.empty()) playerList.clear();
    if (!gameField.empty()) gameField.clear();
    if (banker!=nullptr) delete banker;
    if (deck!=nullptr) delete deck;
}

QGraphicsScene* & GameManager::init(QWidget* mainWin){
    if (gameFieldScene!=nullptr) delete gameFieldScene;
    if (!gameField.empty()) gameField.clear();
    if (!playerList.empty()) playerList.clear();
    gameFieldScene=new QGraphicsScene();
    QFile file(":/map_data/map.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream fin(&file);
    Box* jail;
    while (!fin.atEnd()){
        unsigned id, price, rent;
        QString line, name;
        Box* b;
        QString path;
        fin>>id>>name;
        if (id%7==0 || name=="email"){
            if (id==7){
                b=new Jail(id, name);
            }else b=new Box(id,name);
            path=(":/img/nonProperty/")+(b->getName())+(".png");
        }else if(id==4||id==11||id==17||id==24){
            fin>>price>>rent;
            b=new Restaurant(id,name,price,rent);
            path=(":/img/propertyAsset/")+(b->getName())+("B.png");
        }else{
            Color c;
            fin>>price>>rent;
            if (id<7) c=Yellow;
            else if (id<14) c=Blue;
            else if (id<21) c=Green;
            else c=Red;
            b=new BuildableProperty(id,(name),c,price,rent);
            path=(":/img/propertyAsset/")+(b->getName())+("B.png");
        }
        if ( b->getId()<7){
            b->setRotation(180);
            if (b->getId()==0){
                b->setPos(0,0);
                b->setP1Position(b->x()-130,b->y()-120);
            }else{
                b->setPos((b->getId())*90,0);
                b->setP1Position(gameField.front()->getP1XPosition()+130+90*(b->getId()-1),gameField.front()->getP1YPosition());
            }
        }else if (b->getId()<14){
            if (b->getId()==7){
                jail=b;
                b->setPos(540,-130);
                b->setP1Position(gameField.back()->getP1XPosition()+110,gameField.back()->getP1YPosition()-50);
                static_cast<Jail*>(jail)->setJailP1Position(jail->getP1XPosition(),jail->getP1YPosition()+40);
            }else if (b->getId()==8){
                b->setRotation(-90);
                b->setPos(540,(b->getId()-7)*90);
                b->setP1Position(gameField.back()->getP1XPosition(),gameField.back()->getP1YPosition()+130);
            }else{
                b->setRotation(-90);
                b->setPos(540,(b->getId()-7)*90);
                b->setP1Position(gameField.back()->getP1XPosition(),gameField.back()->getP1YPosition()+90);
            }
        }else if (b->getId()<21){
            if (b->getId()==14){
                b->setPos(540,540);
                b->setP1Position(gameField.back()->getP1XPosition(),gameField.back()->getP1YPosition()+100);
            }else{
                b->setPos(630-(b->getId()-13)*90,540);
                b->setP1Position(gameField.back()->getP1XPosition()-90,gameField.back()->getP1YPosition());
            }
        } else {
            b->setRotation(90);
            if (b->getId()==21){
                b->setPos(0,540);
                b->setP1Position(gameField.back()->getP1XPosition()-130,gameField.back()->getP1YPosition());
            }else{
                b->setPos(0,630-(b->getId()-20)*90);
                b->setP1Position(gameField.back()->getP1XPosition(),gameField.back()->getP1YPosition()-90);
            }
        }
        gameField.push_back(b);
        b->setPixmap(QPixmap(path));
        gameFieldScene->addItem(b);
    }
    file.close();
    bool ok=false;
    numOfPlayer=QInputDialog::getInt(mainWin,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        for (unsigned i=1;i<=numOfPlayer;++i){
            bool ok=false;
            QString p_name=QInputDialog::getText(mainWin,"",QString("Plaese input player %1 name").arg(QString::number(i)),QLineEdit::Normal,"", &ok);
            if (ok){
                Player* p=new Player(i,p_name);
                playerList.push_back(p);
                QString path;
                path=((":/img/character/character")+QString::number(i)+(".png"));
                p->setPixmap(QPixmap(path));
                playerPositionSetter(playerList.back(),gameField.front());
                gameFieldScene->addItem(p);
            }
        }
    }
    currentPlayer=playerList.front();
    deck->shuffle();
    return gameFieldScene;
}

Player* & GameManager::getCurrentPlayer(){
    return currentPlayer;
}

void GameManager::moveToNextPlayer(){
    if (checkBankrupt()){
        QMessageBox* loseMsg=new QMessageBox();
        loseMsg->setText("Player"+QString::number(currentPlayer->getId())+" bankrupted! sosad");
        loseMsg->exec();
        for (int i=0;i<currentPlayer->getOwnedPropertyList().size();++i){
            Property* target=static_cast<Property*>(gameField[currentPlayer->getOwnedPropertyList()[i]]);
            target->resetter();
        }
        delete loseMsg;
        gameFieldScene->removeItem(currentPlayer);
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
    Box* b=(gameField[(currentPlayer->getPosition()+u)%28]);
    if (currentPlayer->getPosition()>(b)->getId()) (*currentPlayer)+=2000;
    playerPositionSetter(currentPlayer,b);
    currentPlayer->setPosition((b)->getId());
    QMessageBox* rentMessage=new QMessageBox();
    rentMessage->setStandardButtons(QMessageBox::Ok);
    rentMessage->setDefaultButton(QMessageBox::Ok);
    qDebug()<<"t1";
    if(typeid ((*b))==typeid (BuildableProperty)){
        qDebug()<<"t2";
        BuildableProperty *bp=static_cast<BuildableProperty*>(b);
        qDebug()<<"t3";
        if(bp->getOwnerId()!=0 && bp->getOwnerId()!=currentPlayer->getId() && !bp->getMortgage()){
            Player* owner=playerList[bp->getOwnerId()-1];
            unsigned numOfSameColor=0;
            for (int i=0;i<owner->getOwnedPropertyList().size();++i){
                if (static_cast<BuildableProperty*>(gameField[owner->getOwnedPropertyList()[i]])->getColor()==bp->getColor())
                    ++numOfSameColor;
                if (numOfSameColor>=2)
                    break;
            }
            (*currentPlayer)-=bp->getRentOfProperty()*numOfSameColor;
            qDebug()<<"rent"<<currentPlayer->getId()<<owner->getId()<<bp->getName()<<bp->getId();
            (*owner)+=(bp->getRentOfProperty())*numOfSameColor;
            qDebug()<<"t7";
            rentMessage->setInformativeText("You have to pay $"+QString::number(bp->getRentOfProperty())+"for rent.");
            qDebug()<<"t8";
            rentMessage->exec();
        }
    }else if (typeid ((*b))==typeid (Restaurant)){
        qDebug()<<"t2";
        Restaurant *r=static_cast<Restaurant*>(b);
        qDebug()<<"t3";
        if(r->getOwnerId()!=0 && r->getOwnerId()!=currentPlayer->getId() && !r->getMortgage()){
            qDebug()<<"t4";
            Player* owner=playerList[r->getOwnerId()-1];
            unsigned numOfRestaurant=owner->getNumOfRestaurant();
            qDebug()<<"rent"<<currentPlayer->getId()<<owner->getId()<<r->getName()<<r->getId();
            (*currentPlayer)-=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t6";
            (*owner)+=r->getRentOfProperty(numOfRestaurant-1);
            qDebug()<<"t7";
            rentMessage->setInformativeText(r->getName()+" is owned by other player\nYou have to pay $"+QString::number(r->getRentOfProperty(numOfRestaurant-1))+" for rent.");
            qDebug()<<"t8";
            rentMessage->exec();
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
    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    int choice=emailContent->exec();
    if (choice==QMessageBox::Ok){

        e->emailAction(currentPlayer);
    }

    if(deck->isCompletelyUsed()){
        deck->shuffle();
    }else qDebug()<<"not completely Used the deck";

    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    Box* newLocation=gameField[currentPlayer->getPosition()];
    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();
    qDebug()<<"et1";

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
