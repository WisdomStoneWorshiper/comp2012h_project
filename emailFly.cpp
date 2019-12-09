#include "emailFly.h"


EmailFly::~EmailFly(){}

EmailFly::EmailFly(int cardOrder){

   //++cardOrder;

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
            setMessage(getMessage()+"Adance to UniBar\n");
            cardIndex =3;
            break;
        case 4:
            setMessage(getMessage()+"Adance to PresidnetLodge\n");
            cardIndex =4;
            break;

    }


}

void EmailFly::function(Player *p){ //return the id of map position
    switch (cardIndex){
//        case 1:

//        case 2:

//        case 3:

//        case 4:

    }

}
