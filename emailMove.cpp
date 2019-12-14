#include "emailMove.h"


EmailMove::~EmailMove(){}

EmailMove::EmailMove(int cardOrder){//assign corresponding emailIndex by the emailOrder from emailDeck
    switch (cardOrder){
        case 1:
            setMessage(getMessage()+"\nDear student,\n\nJust a gentle reminder that a make-up class will be conducted Now at Rm 2304.\nThanks, and see you. :)\n\nBest,\nDesmond ");
            cardIndex =1;
            break;
        case 2:
            setMessage(getMessage()+"\nGo to school entry (starting point)\n");
            cardIndex =2;
            break;
        case 3:
            setMessage(getMessage()+"\nDear student,\n\nComp2012h class gathering are held on UniBar,\n\nCome join us\nAdance to UniBar\nThanks, and see you. :)\n\nBest,\nDesmond");
            cardIndex =3;
            break;
        case 4:
            setMessage(getMessage()+"\nInvite Letter from President!\nAdance to PresidnetLodge\n");
            cardIndex =4;
            break;
        case 5:
            setMessage(getMessage()+"\nYou are the representive of your department !\nAdance to Swimming Pool\n");
            cardIndex =5;
            break;
    }
}

void EmailMove::emailAction(Player *p){ //return the id of map position
    switch (cardIndex){
        case 1:
            setMessage("\n"+p->getPlayerInfo()+"\n");
            p->setPosition(7);  
            p->setinJail(true);
            break;
        case 2:
            setMessage("\n"+p->getPlayerInfo()+"\n");
            p->setPosition(0);
            break;
        case 3:
            setMessage("\n"+p->getPlayerInfo()+"\n");
            p->setPosition(20);
            break;
        case 4:
            setMessage("\n"+p->getPlayerInfo()+"\n");
            p->setPosition(27);
            break;
        case 5:
         setMessage("\n"+p->getPlayerInfo()+"\n");
            p->setPosition(8);
            break;
    }
}
