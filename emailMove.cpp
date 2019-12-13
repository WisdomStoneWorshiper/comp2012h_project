#include "emailMove.h"


EmailMove::~EmailMove(){}

EmailMove::EmailMove(int cardOrder){//assign corresponding emailIndex by the emailOrder from emailDeck



    switch (cardOrder){
        case 1:
            setMessage(getMessage()+"You have a make up class\nGo take the class now!\n");
            cardIndex =1;
            break;
        case 2:
            setMessage(getMessage()+"Go to school entry (starting point)\n");
            cardIndex =2;
            break;
        case 3:
            setMessage(getMessage()+"Comp2012h class gathering!\nAdance to UniBar\n");
            cardIndex =3;
            break;
        case 4:
            setMessage(getMessage()+"Invite Letter from President!\nAdance to PresidnetLodge\n");
            cardIndex =4;
            break;
        case 5:
            setMessage(getMessage()+"You are the representive of your department !\nAdance to Swimming Pool\n");
            cardIndex =5;
            break;

    }


}

void EmailMove::emailAction(Player *p){ //return the id of map position
    switch (cardIndex){
        case 1:
            p->setPosition(7);
            p->setinJail(true);
            break;
        case 2:
            p->setPosition(0);
            break;
        case 3:
            p->setPosition(20);
            break;
        case 4:
            p->setPosition(27);
            break;
        case 5:
            p->setPosition(8);
            break;
    }

}
