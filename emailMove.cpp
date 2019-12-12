#include "emailMove.h"


EmailMove::~EmailMove(){}

EmailMove::EmailMove(int cardOrder){//assign corresponding emailIndex by the emailOrder from emailDeck



    switch (cardOrder){
        case 1:
            setMessage(getMessage()+"Go take the class now!\n");
            cardIndex =1;
            break;
        case 2:
            setMessage(getMessage()+"Adance to Starting Point\n");
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

    }

}
