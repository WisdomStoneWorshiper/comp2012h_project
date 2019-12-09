#include "emailMoney.h"


EmailMoney::~EmailMoney(){}

EmailMoney::EmailMoney(int cardOrder){

    switch (cardOrder){
        case 1:
            setMessage(getMessage()+"You got $1000 scholarship\n");
            cardIndex = 1;
            break;
        case 2:
            setMessage(getMessage()+"You got $500 refund from SU \n");
            cardIndex = 2;
            break;
        case 3:
            setMessage(getMessage()+"Pay $500 for printing quota\n");
            cardIndex = 3;
            break;
        case 4:
            setMessage(getMessage()+"Pay $1000 for Hall fee\n");
            cardIndex = 4;
            break;
        case 5:
            setMessage(getMessage()+"You got $200 after doing assignment for others");
            cardIndex = 5;
            break;
        case 6:
            setMessage(getMessage()+"Pay $500 for add octopus card valuse");
            cardIndex = 6;

    }
}



void EmailMoney::function(Player *p){
    switch (cardIndex){
        case 1:
            *p+1000;
            break;
        case 2:
            *p+500;
            break;
        case 3:
            *p-500;
            break;
        case 4:
            *p-1000;
            break;
        case 5:
            *p+200;
            break;
        case 6:
            *p-500;
            break;

    }
}
