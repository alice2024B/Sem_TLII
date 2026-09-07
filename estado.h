#ifndef ESTADO_H
#define ESTADO_H

#include "elementoPila.h"

using namespace std;

class Estado : public ElementoPila
{
private:
    int estado;

public:
    Estado(int estado)
    {
        this->estado = estado;
    }

    int getEstado()
    {
        return estado;
    }

    void muestra()
    {
        cout << estado;
    }
};

#endif