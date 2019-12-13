#include "emailGetMoney.h"


EmailGetMoney::~EmailGetMoney(){}

EmailGetMoney::EmailGetMoney(int emailOrder){ //assign corresponding emailIndex by the emailOrder from emailDeck


    switch (emailOrder){
        case 1:
            setMessage(getMessage()+"\nYou got $1000 scholarship\n");
            emailIndex = 1;
            break;
        case 2:
            setMessage(getMessage()+"\nYou got $500 refund from SU \n");
            emailIndex = 2;
            break;
        case 3:
            setMessage(getMessage()+"\nPay $500 for printing quota\n");
            emailIndex = 3;
            break;
        case 4:
            setMessage(getMessage()+"\nPay $1000 for Hall fee\n");
            emailIndex = 4;
            break;
        case 5:
            setMessage(getMessage()+"\nYou got $200 ");
            emailIndex = 5;
            break;
        case 6:
            setMessage(getMessage()+"\nPay $500 for add octopus card valuse");
            emailIndex = 6;
            break;
        case 7:
            setMessage(getMessage()+"\n$1000 Scholarship from Desmond for students who have 3.0 GPA or above\n");
            emailIndex = 7;
            break;
    }
}



void EmailGetMoney::emailAction(Player *p){
    switch (emailIndex){
        case 1:
            *p+=1000;
            break;
        case 2:
            *p+=500;
            break;
        case 3:
            *p-=500;
            break;
        case 4:
            *p-=1000;
            break;
        case 5:
            *p+=200;
            break;
        case 6:
            *p-=500;
            break;
        case 7:
            if(p->getGpa()>3)
                *p+=1000;
            break;

    }
}
