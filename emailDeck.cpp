#include "emailDeck.h"

EmailDeck::EmailDeck(){

        for(int i =1; i<=4 ; ++i){
            EmailFly * p = new EmailFly(i);
            deck.push_back(p);
        }

        for(int i =1; i<=6 ; ++i){
            EmailMoney * p = new EmailMoney(i);
            deck.push_back(p);
        }

        deck.push_back(new EmailJailPass);

        emailOrder = deck.begin();


}
EmailDeck::~EmailDeck(){

    for(unsigned i = 0; deck[i]!=deck.back();++i)
        delete deck[i];
}


void EmailDeck::shuffle(){ //shuffle before isEmpty function
     std::random_shuffle ( deck.begin(), deck.end() );
}

bool EmailDeck::isCompletelyUsed(){
    return emailOrder == deck.begin();
}

Email * EmailDeck ::getEmail(){

    deque<Email*>:: iterator temp;
    temp = emailOrder;
    emailOrder ++;
    return *temp;

}
