#ifndef PILA_H
#define PILA_H

#include <list>
#include "elementoPila.h"

using namespace std;

class Pila
{
private:
    list<ElementoPila*> lista;

public:
    void push(ElementoPila *x);
    ElementoPila* pop();
    ElementoPila* top();
    void muestra();
};

#endif