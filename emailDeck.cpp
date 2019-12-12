#include "emailDeck.h"

EmailDeck::EmailDeck(){ 
        for(int i =1; i<=5 ; ++i){
            EmailMove * p = new EmailMove(i);
            deck.push_back(p);
        }

        for(int i =1; i<=7 ; ++i){
            EmailGetMoney * p = new EmailGetMoney(i);// create Email with a emailOrder parameter
            deck.push_back(p);
        }

        deck.push_back(new EmailGetJailPass);

        emailOrder = deck.begin();

}
EmailDeck::~EmailDeck(){


//    for(unsigned i = 0; deck[i]!=deck.back();++i)
//        delete deck[i];
    deck.clear();

}


void EmailDeck::shuffle(){ //shuffle before the dequee isCompletelyUsed

     std::random_shuffle ( deck.begin(), deck.end() );

}

bool EmailDeck::isCompletelyUsed()const { //check if the double end queue go back to the first
    return emailOrder == deck.begin();
}

Email * EmailDeck ::getEmail(){

    deque<Email*>:: iterator temp;
    temp = emailOrder;
    emailOrder ++;
    return *temp;

}
