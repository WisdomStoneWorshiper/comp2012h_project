#ifndef BANKER_H
#define BANKER_H

#include "charactor.h"

class Banker: public Charactor{

public:
    //Banker();
    Banker(unsigned short);
    Banker(const Banker&);
    ~Banker();
    void addMortgage(Property*);
    void foreclosure(Property*);
private:
    list <Property*> mortgage_list;
};

#endif // BANKER_H
