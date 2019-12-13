#include "emailGetJailPass.h"

EmailGetJailPass::EmailGetJailPass(){

        setMessage(getMessage()+"\nAccording to your outstanding mid-term result,\nyou don't need to attend the make up class!\n\nYou got an \"Escape Pass\" :)");
}

void EmailGetJailPass::emailAction(Player *p){
    setMessage("\n"+p->getPlayerInfo()+"\n");
    p->changeJailPass();

}
EmailGetJailPass::~EmailGetJailPass(){}
