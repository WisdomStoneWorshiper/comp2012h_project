#include "emailFly.h"


EmailFly::~EmailFly(){}

EmailFly::EmailFly(int cardOrder){



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

void EmailFly::emailAction(Player *p){ //return the id of map position
    switch (cardIndex){
//        case 1:

//        case 2:

//        case 3:

//        case 4:

//        case 5:

//        case 6:

    }

}
