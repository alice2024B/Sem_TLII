#include <iostream>
#include <string>

#include "pila.h"
#include "terminal.h"
#include "noTerminal.h"
#include "estado.h"

using namespace std;

#define MAX 100

int tablaLR1[5][4] =
{
    { 2,  0,  0,  1 },
    { 0,  0, -1,  0 },
    { 0,  3,  0,  0 },
    { 4,  0,  0,  0 },
    { 0,  0, -2,  0 }
};

int tablaLR2[5][4] =
{
    { 2,  0,  0,  1 },
    { 0,  0, -1,  0 },
    { 0,  3, -3,  0 },
    { 2,  0,  0,  4 },
    { 0,  0, -2,  0 }
};


/* Identificador del no terminal de cada regla */
int idReglas[2] = { 3, 3 };

/* Cantidad de simbolos del lado derecho */
int lonReglas[2] = { 3, 1 };


/* Obtener el siguiente simbolo de la entrada */
int siguienteSimbolo(string entrada, int &pos, string &simbolo)
{
    simbolo = "";

    /* Identificador */
    if ((entrada[pos] >= 'a' && entrada[pos] <= 'z') ||
        (entrada[pos] >= 'A' && entrada[pos] <= 'Z'))
    {
        while ((entrada[pos] >= 'a' && entrada[pos] <= 'z') ||
               (entrada[pos] >= 'A' && entrada[pos] <= 'Z') ||
               (entrada[pos] >= '0' && entrada[pos] <= '9'))
        {
            simbolo += entrada[pos];
            pos++;
        }

        return 0;
    }

    /* Signo + */
    if (entrada[pos] == '+')
    {
        simbolo = "+";
        pos++;

        return 1;
    }

    /* Fin de entrada */
    if (entrada[pos] == '\0')
    {
        simbolo = "$";

        return 2;
    }

    /* Simbolo no reconocido */
    simbolo += entrada[pos];
    pos++;

    return -1;
}


/* EJERCICIO 1
   E -> id + id
*/
void ejercicio1()
{
    string entrada;
    string simbolo;

    int pos = 0;
    int tipo;
    int fila;
    int columna;
    int accion;
    bool aceptacion = false;

    cout << endl;
    cout << "=====================================" << endl;
    cout << "          EJERCICIO 1" << endl;
    cout << "=====================================" << endl;

    cout << "Gramatica: E -> id + id" << endl;
    cout << "Ingrese la entrada: ";
    cin >> entrada;

    Pila pila;

    /* Pila inicial */
    pila.push(new Terminal("$"));
    pila.push(new Estado(0));

    /* Leer primer simbolo */
    tipo = siguienteSimbolo(entrada, pos, simbolo);

    while (!aceptacion)
    {
        if (tipo < 0)
        {
            cout << endl;
            pila.muestra();
            cout << "Entrada: " << simbolo << endl;
            cout << "Error: entrada no valida" << endl;
            break;
        }

        Estado *estadoActual =
            dynamic_cast<Estado*>(pila.top());

        if (estadoActual == nullptr)
        {
            cout << "Error en la pila" << endl;
            break;
        }

        fila = estadoActual->getEstado();
        columna = tipo;

        accion = tablaLR1[fila][columna];

        cout << endl;
        pila.muestra();
        cout << "Entrada: " << simbolo << endl;

        if (accion > 0)
        {
            cout << "Accion: d" << accion << endl;

            /* Meter el terminal */
            pila.push(new Terminal(simbolo));

            /* Meter el estado */
            pila.push(new Estado(accion));

            /* Leer siguiente simbolo */
            tipo = siguienteSimbolo(entrada, pos, simbolo);
        }
        else if (accion == -2)
        {
            cout << "Accion: r1 -> E -> id + id" << endl;

            /* Quitar id, estado, +, estado, id, estado */
            pila.pop();
            pila.pop();
            pila.pop();
            pila.pop();
            pila.pop();
            pila.pop();

            Estado *estado =
                dynamic_cast<Estado*>(pila.top());

            fila = estado->getEstado();

            /* GOTO de E */
            accion = tablaLR1[fila][3];

            pila.push(new NoTerminal("E"));
            pila.push(new Estado(accion));
        }
        else if (accion == -1)
        {
            cout << "Accion: r0" << endl;
            cout << "Aceptacion" << endl;

            aceptacion = true;
        }
        else
        {
            cout << "Error: entrada no valida" << endl;
            break;
        }
    }
}

/* EJERCICIO 2
   E -> id + E | id
*/
void ejercicio2()
{
    string entrada;
    string simbolo;

    int pos = 0;
    int tipo;
    int fila;
    int columna;
    int accion;
    int regla;
    int longitud;

    bool aceptacion = false;

    cout << endl;
    cout << "=====================================" << endl;
    cout << "          EJERCICIO 2" << endl;
    cout << "=====================================" << endl;

    cout << "Gramatica: E -> id + E | id" << endl;
    cout << "Ingrese la entrada: ";
    cin >> entrada;

    Pila pila;

    /* Pila inicial */
    pila.push(new Terminal("$"));
    pila.push(new Estado(0));

    /* Leer primer simbolo */
    tipo = siguienteSimbolo(entrada, pos, simbolo);

    while (!aceptacion)
    {
        if (tipo < 0)
        {
            cout << endl;
            pila.muestra();
            cout << "Entrada: " << simbolo << endl;
            cout << "Error: entrada no valida" << endl;
            break;
        }

        Estado *estadoActual =
            dynamic_cast<Estado*>(pila.top());

        if (estadoActual == nullptr)
        {
            cout << "Error en la pila" << endl;
            break;
        }

        fila = estadoActual->getEstado();
        columna = tipo;

        accion = tablaLR2[fila][columna];

        cout << endl;
        pila.muestra();
        cout << "Entrada: " << simbolo << endl;

        if (accion > 0)
        {
            cout << "Accion: d" << accion << endl;

            /* Desplazamiento */
            pila.push(new Terminal(simbolo));
            pila.push(new Estado(accion));

            /* Leer siguiente simbolo */
            tipo = siguienteSimbolo(entrada, pos, simbolo);
        }
        else if (accion < 0)
        {
            /* Aceptacion */
            if (accion == -1)
            {
                cout << "Accion: r0" << endl;
                cout << "Aceptacion" << endl;

                aceptacion = true;
            }
            else
            {
              
                regla = -accion - 2;

                if (regla < 0 || regla >= 2)
                {
                    cout << "Error: reduccion no valida" << endl;
                    break;
                }

                if (regla == 0)
                {
                    cout << "Accion: r1 -> E -> id + E" << endl;
                }
                else
                {
                    cout << "Accion: r2 -> E -> id" << endl;
                }

                longitud = lonReglas[regla];

                for (int i = 0; i < longitud; i++)
                {
                    pila.pop();
                    pila.pop();
                }

                Estado *estado =
                    dynamic_cast<Estado*>(pila.top());

                fila = estado->getEstado();

                /* GOTO de E */
                columna = idReglas[regla];

                accion = tablaLR2[fila][columna];

                pila.push(new NoTerminal("E"));
                pila.push(new Estado(accion));
            }
        }
        else
        {
            cout << "Error: entrada no valida" << endl;
            break;
        }
    }
}


int main()
{
    int opcion;

    cout << "=====================================" << endl;
    cout << "      MINI ANALIZADOR SINTACTICO" << endl;
    cout << "               LR(1)" << endl;
    cout << "=====================================" << endl;
    cout << endl;

    cout << "1. Ejercicio 1" << endl;
    cout << "2. Ejercicio 2" << endl;
    cout << "Seleccione una opcion: ";

    cin >> opcion;

    if (opcion == 1)
    {
        ejercicio1();
    }
    else if (opcion == 2)
    {
        ejercicio2();
    }
    else
    {
        cout << "Opcion no valida." << endl;
    }

    return 0;
}