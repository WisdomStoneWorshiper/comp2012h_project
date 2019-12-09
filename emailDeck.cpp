#include "emailDeck.h"

EmailDeck::EmailDeck(){

        for(int i =1; i<=4 ; ++i){
            EmailFly * p = new EmailFly(i);
            cardDeck.push_back(p);
        }

        for(int i =1; i<=4 ; ++i){
            EmailMoney * p = new EmailMoney(i);
            cardDeck.push_back(p);
        }

        EmailJailPass * p = new EmailJailPass;
        cardDeck.push_back(p);

        std::random_shuffle ( cardDeck.begin(), cardDeck.end() );

}





