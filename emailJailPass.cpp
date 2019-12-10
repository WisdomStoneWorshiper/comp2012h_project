#include "emailJailPass.h"

EmailJailPass::EmailJailPass(){

        setMessage(getMessage()+"This email for escape the class");
}

void EmailJailPass::emailAction(Player *p){
    p->changeJailPass();
}
EmailJailPass::~EmailJailPass(){}
