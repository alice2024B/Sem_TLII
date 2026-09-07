# Práctica 3 - Analizador Sintáctico LR(1)
## Implementación usando Objetos
### Objetivo
Modificar el analizador sintáctico LR(1) de la práctica anterior para utilizar una pila de objetos en lugar de una pila de enteros.
Con esta modificación, los elementos que forman la pila se pueden representar mediante objetos y mostrar de una forma más parecida al análisis manual.

## Desarrollo
Para realizar esta práctica se modificó la pila utilizada en la práctica anterior.
Primero se creó la clase 'ElementoPila', que funciona como la clase base. Después se crearon las clases:
- 'Terminal'
- 'noTerminal'
-  'Estado'
Estas tres clases heredan de 'ElementoPila'.
También se modificaron las funciones 'push', 'pop', 'top' y 'muestra' de la clase 'pila' para trabajar con objetos de tipo 'ElementoPila*'.

## Clase ElementoPila
Esta clase sirve como base para los diferentes elementos que pueden almacenarse en la pila.

class ElementoPila
{
public:
    virtual void muestra() = 0;
    virtual ~ElementoPila() {}
};

El método 'muestra()' es virtual para cada clase pueda mostrar su información de acuerdo con el tipo de objeto.
## Clase terminal
La clase 'terminal' representa los símbolos terminales utilizados por el analizador.

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

Por ejemplo, los símbolos 'id', '+' y'$' pueden representarse mediante objetos de esta clase.

