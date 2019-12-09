#include "email.h"

Email::Email(){
    message = "You got an Email from Desmond!!\n";
}

QString Email::getMessage () const {
   return message;
}

void Email::setMessage(QString s){
    message = s;
}
Email::~ Email(){

}
