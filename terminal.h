#ifndef TERMINAL_H
#define TERMINAL_H

#include "elementoPila.h"
#include <string>

using namespace std;

class Terminal : public ElementoPila
{
private:
    string simbolo;

public:
    Terminal(string simbolo)
    {
        this->simbolo = simbolo;
    }

    void muestra()
    {
        cout << simbolo;
    }
};

#endif