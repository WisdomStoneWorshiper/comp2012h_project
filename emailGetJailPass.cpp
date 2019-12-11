#include "emailGetJailPass.h"

EmailGetJailPass::EmailGetJailPass(){

        setMessage(getMessage()+"This email for escape the class\n");
}

void EmailGetJailPass::emailAction(Player *p){
    p->changeJailPass();
}
EmailGetJailPass::~EmailGetJailPass(){}
