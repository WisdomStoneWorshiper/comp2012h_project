#include "gameManager.h"
#include <QDebug>


GameManager::GameManager():deck(new EmailDeck())
{
    gameFieldScene=nullptr;
}

//destructor of GameManager
GameManager::~GameManager(){
    for (vector<Player*>::const_iterator target=playerList.begin();target!=playerList.end();++target){
        delete *target;
    }
    for (vector<Box*>::const_iterator target=gameField.begin();target!=gameField.end();++target){
        delete *target;
    }

    if (!playerList.empty()) playerList.clear();
    if (!gameField.empty()) gameField.clear();
    if (deck!=nullptr) delete deck;
    if (gameFieldScene!=nullptr) delete gameFieldScene;
}

//this function is used to initalize the game
QGraphicsScene* & GameManager::init(QWidget* mainWin){
    //the code below is reset the game property if it is not the first game on the run time
    if (gameFieldScene!=nullptr)
        delete gameFieldScene;
    gameFieldScene=new QGraphicsScene();
    if (!gameField.empty()){
        for (vector<Box*>::const_iterator target=gameField.begin();target!=gameField.end();++target){
            delete *target;
        }
        gameField.clear();
    }
    if (!playerList.empty()) {
        for (vector<Player*>::const_iterator target=playerList.begin();target!=playerList.end();++target){
            delete *target;
        }
        playerList.clear();
    }
    //the code below is initalizing the Box object
    //first it load a text file contain Box property
    QFile file(":/map_data/map.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }
    QTextStream fin(&file);
    while (!fin.atEnd()){
        unsigned id, price, rent;
        QString line, name;
        Box* b;
        QString path;
        fin>>id>>name;
        //this if statement is determinating which sub-class of this box belongs to
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
        //this if statement is setting the graphical view of the box object
        if (b->getId()<7){
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
                b->setPos(540,-130);
                b->setP1Position(gameField.back()->getP1XPosition()+110,gameField.back()->getP1YPosition()-50);
                static_cast<Jail*>(b)->setJailP1Position(b->getP1XPosition(),b->getP1YPosition()+40);
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
        //after all property of box is setted, it pushed into a vector container
        gameField.push_back(b);
        b->setPixmap(QPixmap(path));
        //qDebug()<<"on91";
        gameFieldScene->addItem(b);
    }
    file.close();
    bool ok=false;
    //this code below is initalizing player object
    numOfPlayer=QInputDialog::getInt(mainWin,"","Plaese input number of player (2-6)",3,2,6,1,&ok);
    if (ok){
        for (unsigned i=1;i<=numOfPlayer;++i){
            bool validName=false;
            while(validName==false){
                validName=true;
            bool ok=false;
            QString p_name=QInputDialog::getText(mainWin,"",QString("Plaese input player %1 name").arg(QString::number(i)),QLineEdit::Normal,"", &ok);
            if (ok){
                qDebug()<<"name"<<p_name;
                if (!playerList.empty()){
                for (int i=0;i<playerList.size();++i){
                    if (p_name.isEmpty() ||(!playerList.empty() && p_name.compare(playerList[i]->getName())==0)){
                        validName=false;
                        break;
                    }
                }
                }else{
                     if (p_name.isEmpty() )
                         validName=false;
                }
                if (validName){
                Player* p=new Player(i,p_name);
                playerList.push_back(p);
                QString path;
                path=((":/img/character/character")+QString::number(i)+(".png"));
                p->setPixmap(QPixmap(path));
                playerPositionSetter(p,gameField.front());
                gameFieldScene->addItem(p);
                }else{
                    QMessageBox *invalidNameMsg=new QMessageBox();
                    invalidNameMsg->setText("Name cannot be empty and must be unique");
                    invalidNameMsg->exec();
                    delete invalidNameMsg;
                }
            }
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

//this function is used to find and set current player
void GameManager::moveToNextPlayer(){
    //if current player bankrupted (lose the game), reset the property owned by him/her
    if (checkBankrupt()){
        QMessageBox* loseMsg=new QMessageBox();
        loseMsg->setText("Player"+QString::number(currentPlayer->getId())+" bankrupted! sosad");
        loseMsg->exec();
        for (int i=0;i<currentPlayer->getOwnedPropertyList().size();++i){
            Property* target=static_cast<Property*>(gameField[currentPlayer->getOwnedPropertyList()[i]]);
            target->resetter();
        }
        delete loseMsg;
        currentPlayer->setLosed();
        gameFieldScene->removeItem(currentPlayer);
    }
    //find next player who is not bankrupted
    do{
        if (currentPlayer!=playerList[numOfPlayer-1]){
            currentPlayer=playerList[currentPlayer->getId()];
        }
        else
            currentPlayer=playerList[0];
    }while (currentPlayer->checkLosed()) ;

}

//this function is used to handle moving player
void GameManager::movePlayer(unsigned u){
    //first find the box player need to move to
    Box* currentBox=(gameField[(currentPlayer->getPosition()+u)%28]);
    if (currentPlayer->getPosition()>(currentBox)->getId()) (*currentPlayer)+=2000;
    playerPositionSetter(currentPlayer,currentBox);
    currentPlayer->setPosition((currentBox)->getId());
    QMessageBox* rentMessage=new QMessageBox();
    rentMessage->setStandardButtons(QMessageBox::Ok);
    rentMessage->setDefaultButton(QMessageBox::Ok);
    //Check whether the box have speacial action needed to be done
    //since BuildableProperty and Restaurant need to pay rent and they have two type of rent calculation
    //so they are seperated
    if(typeid ((*currentBox))==typeid (BuildableProperty)){
        BuildableProperty *target=static_cast<BuildableProperty*>(currentBox);
        if(target->getOwnerId()!=0 && target->getOwnerId()!=currentPlayer->getId() && !target->getMortgage()){
            Player* owner=playerList[target->getOwnerId()-1];
            unsigned numOfSameColor=0;
            for (int i=0;i<owner->getOwnedPropertyList().size();++i){
                if (static_cast<BuildableProperty*>(gameField[owner->getOwnedPropertyList()[i]])->getColor()==target->getColor())
                    ++numOfSameColor;
                if (numOfSameColor>=2)
                    break;
            }
            (*currentPlayer)-=target->getRentOfProperty()*numOfSameColor;
            (*owner)+=(target->getRentOfProperty())*numOfSameColor;
            rentMessage->setInformativeText("You have to pay $"+QString::number(target->getRentOfProperty())+"for rent.");
            rentMessage->exec();
        }
    }else if (typeid ((*currentBox))==typeid (Restaurant)){
        Restaurant *currentRestaurant=static_cast<Restaurant*>(currentBox);
        if(currentRestaurant->getOwnerId()!=0 && currentRestaurant->getOwnerId()!=currentPlayer->getId() && !currentRestaurant->getMortgage()){
            Player* owner=playerList[currentRestaurant->getOwnerId()-1];
            unsigned numOfRestaurant=owner->getNumOfRestaurant();
            (*currentPlayer)-=currentRestaurant->getRentOfProperty(numOfRestaurant-1);
            (*owner)+=currentRestaurant->getRentOfProperty(numOfRestaurant-1);
            rentMessage->setInformativeText(currentRestaurant->getName()+" is owned by other player\nYou have to pay $"+QString::number(currentRestaurant->getRentOfProperty(numOfRestaurant-1))+" for rent.");
            rentMessage->exec();
        }
    }else if(QString::compare((currentBox)->getName(),"Email",Qt::CaseInsensitive)==0){ //
        emailAction(currentBox);
    }else if(QString::compare((currentBox)->getName(),"TakeTheClass",Qt::CaseInsensitive)==0){

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
        movePlayer(14); //jail id = 14

    }
    delete rentMessage;
}

//move a player to a box
void GameManager::playerPositionSetter(Player *p, Box *b){
    //if player need to go to jail and have a jail pass, place him/she in just passing
    if (p->getJailPass() && p->checkInJail()){
        p->setinJail(false);
        p->changeJailPass();
        QMessageBox usePassMsg;
        usePassMsg.setText("Lucky! You have a \"Escape Pass\", You can leave in next round\n\nNow You have no \"Escape Pass\"");
        usePassMsg.exec();
    }
    //if player need to go to jail, place him/she in jail
    if (!(p->checkInJail())){
        if (p->getId()<4){
            p->setPos(b->getP1XPosition()+20*(p->getId()-1),b->getP1YPosition());
        }else
            p->setPos(b->getP1XPosition()+20*(p->getId()-4),b->getP1YPosition()+50);
    }else{ //if not, place in corresponding box
            if (p->getId()<4)
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-1),static_cast<Jail*>(b)->getJailP1YPosition());
            else
                p->setPos(static_cast<Jail*>(b)->getJailP1XPosition()+20*(p->getId()-4),static_cast<Jail*>(b)->getJailP1YPosition()-50);
    }
}

//check whether currentPlayer can buy a Property
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

//check whether the currentPlayer can increase BuildableProperty wifi level
bool GameManager::ableToIncreaseWifi(){
    Box* b=gameField[currentPlayer->getPosition()];
    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostPerLevelOfWifiCoverage() && p->getLevelOfWifiCoverage()<4);
    }
    return false;
}

//check whether the currentPlayer can add a vending machine
bool GameManager::ableToAddVendingMachine(){
    Box* b=gameField[currentPlayer->getPosition()];
    qDebug()<<"av"<<(typeid ((*b))==typeid (BuildableProperty));
    if(typeid ((*b))==typeid (BuildableProperty)){
        BuildableProperty *p=static_cast<BuildableProperty*>(b);
        return (currentPlayer->getId()==p->getOwnerId() && currentPlayer->getMoney()>=p->getCostOfVendingMachine() && p->getNumOfVendingMachines()<1 && p->getLevelOfWifiCoverage()==4);
    }
    return false;
}

//check whether the currentPlayer can do nothing
bool GameManager::checkEndTurn(){
    if(!ableToBuy()&&!ableToIncreaseWifi()) return true;
    return false;
}

//do action of buy property which is stepped by currentPlayer
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

//do action of build something which is stepped by currentPlayer
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

//if currentPlayer stepped on email box, some speacial action will be performed
void GameManager::emailAction(Box* oldLocation){
    //first show the message of the email

    Email * e=deck->getEmail();
    QMessageBox * emailContent=new QMessageBox();
    emailContent->setInformativeText(e->getMessage());
    emailContent->setStandardButtons(QMessageBox::Ok);
    emailContent->setDefaultButton(QMessageBox::Ok);

    //when ok button of the message box is clicked, perform speacial email action
    int choice=emailContent->exec();
    if (choice==QMessageBox::Ok){

        e->emailAction(currentPlayer);
    }

    qDebug()<<"email"<<currentPlayer->getId()<<currentPlayer->getPosition();

    Box* newLocation=gameField[currentPlayer->getPosition()];
    //if the position of player is changed affter the speacial action of the email,
    //move currentPlayer to corresponding position
    if (oldLocation->getId()<(newLocation)->getId()){
        playerPositionSetter(currentPlayer,newLocation);
    }else if(oldLocation->getId()>(newLocation)->getId()){
        (*currentPlayer)+=2000;
        playerPositionSetter(currentPlayer,newLocation);
    }

    if(deck->isLastEmail()){
        qDebug()<<"reach the last email ";
        deck->shuffle();
    }else qDebug()<<"not reach the last email";

    delete emailContent;
}

//return information of currentPlayer
QString GameManager::getCurrentPlayerInfo(){
    qDebug()<<"Info"<<("Player id: "+QString::number(currentPlayer->getId())
              +"\nPlayer name: "+currentPlayer->getName()
              +"\n$: "+QString::number(currentPlayer->getMoney())
              +"\nJail Pass on hand? "+((currentPlayer->getJailPass())?"Yes":"No"));

    return (currentPlayer->getPlayerInfo());
}

//reuturn money after the buying of property
unsigned GameManager::getMoneyAfterBuy(){
    return currentPlayer->getMoney()-static_cast<Property*>(gameField[currentPlayer->getPosition()])->getPropertyPrice();
}

//reuturn money after building something
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

//perform trading property action between player
void GameManager::tradeAction(Player* seller,Property*targetProperty,unsigned price){
    currentPlayer->addProperty(targetProperty);
    seller->removeProperty(targetProperty);
    (*currentPlayer)-=price;
    (*seller)+=price;
}

//perform mortgage action of a property
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

//check whether the winner is exist, if yes, return id of winner, if no, return -1
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
