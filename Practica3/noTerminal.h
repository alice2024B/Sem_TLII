#ifndef NOTERMINAL_H
#define NOTERMINAL_H

#include "elementoPila.h"
#include <string>

using namespace std;

class NoTerminal : public ElementoPila
{
private:
    string simbolo;

public:
    NoTerminal(string simbolo)
    {
        this->simbolo = simbolo;
    }

    void muestra()
    {
        cout << simbolo;
    }
};

#endif